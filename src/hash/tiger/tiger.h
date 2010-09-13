/*
* Tiger
* (C) 1999-2007 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#ifndef BOTAN_TIGER_H__
#define BOTAN_TIGER_H__

#include <botan/mdx_hash.h>

namespace Botan {

/**
* Tiger
*/
class BOTAN_DLL Tiger : public MDx_HashFunction
   {
   public:
      void clear();
      std::string name() const;

      HashFunction* clone() const
         {
         return new Tiger(OUTPUT_LENGTH, PASS);
         }

      /**
      * @param out_size specifies the output length; can be 16, 20, or 24
      * @param passes to make in the algorithm
      */
      Tiger(u32bit out_size = 24, u32bit passes = 3);
   private:
      void compress_n(const byte[], u32bit block);
      void copy_out(byte[]);

      static void pass(u64bit& A, u64bit& B, u64bit& C,
                       const MemoryRegion<u64bit>& M,
                       byte mul);

      static const u64bit SBOX1[256];
      static const u64bit SBOX2[256];
      static const u64bit SBOX3[256];
      static const u64bit SBOX4[256];

      SecureVector<u64bit, 8> X;
      SecureVector<u64bit, 3> digest;
      const u32bit PASS;
   };

}

#endif
