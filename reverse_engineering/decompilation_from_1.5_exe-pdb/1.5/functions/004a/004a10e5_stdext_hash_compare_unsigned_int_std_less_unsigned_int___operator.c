/*
 * Entry: 004a10e5
 * Name: stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>::operator()
 * Namespace: stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>
 * Signature: uint operator()(hash_compare<unsigned_int,std::less<unsigned_int>_> * this, uint * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>::operator()
          (hash_compare<unsigned_int,std::less<unsigned_int>_> *this,uint *param_1)

{
  uint uVar1;
  ldiv_t lVar2;
  
  lVar2 = ldiv((*param_1 ^ 0xdeadbeef) & 0x7fffffff,0x1f31d);
  uVar1 = lVar2.rem * 0x41a7 + lVar2.quot * -0xb14;
  if ((int)uVar1 < 0) {
    uVar1 = uVar1 + 0x7fffffff;
  }
  return uVar1;
}
