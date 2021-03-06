/*
* (C) 2015,2016 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef ECC_HELPERS_H__
#define ECC_HELPERS_H__

#include "fuzzers.h"
#include <botan/curve_gfp.h>
#include <botan/ec_group.h>
#include <botan/reducer.h>

namespace {

inline std::ostream& operator<<(std::ostream& o, const Botan::PointGFp& point)
   {
   o << point.get_affine_x() << "," << point.get_affine_y();
   return o;
   }

void check_ecc_math(const Botan::EC_Group& group,
                    const uint8_t in[], size_t len)
   {
   // These depend only on the group, which is also static
   static const Botan::PointGFp base_point = group.get_base_point();
   static Botan::Blinded_Point_Multiply blind(base_point, group.get_order(), 4);

   const size_t hlen = len / 2;
   const Botan::BigInt a = Botan::BigInt::decode(in, hlen);
   const Botan::BigInt b = Botan::BigInt::decode(in + hlen, len - hlen);

   const Botan::BigInt c = a + b;

   const Botan::PointGFp P = base_point * a;
   const Botan::PointGFp Q = base_point * b;
   const Botan::PointGFp R = base_point * c;

   const Botan::PointGFp A1 = P + Q;
   const Botan::PointGFp A2 = Q + P;

   FUZZER_ASSERT_EQUAL(A1, A2);

   const Botan::PointGFp P1 = blind.blinded_multiply(a, fuzzer_rng());
   const Botan::PointGFp Q1 = blind.blinded_multiply(b, fuzzer_rng());
   const Botan::PointGFp R1 = blind.blinded_multiply(c, fuzzer_rng());

   const Botan::PointGFp S1 = P1 + Q1;
   const Botan::PointGFp S2 = Q1 + P1;

   FUZZER_ASSERT_EQUAL(S1, S2);
   FUZZER_ASSERT_EQUAL(S1, A1);
   }

}

#endif
