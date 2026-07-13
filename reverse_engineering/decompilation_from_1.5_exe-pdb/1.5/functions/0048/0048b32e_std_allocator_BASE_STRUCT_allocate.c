/*
 * Entry: 0048b32e
 * Name: std::allocator<BASE_STRUCT>::allocate
 * Namespace: std::allocator<BASE_STRUCT>
 * Signature: BASE_STRUCT * allocate(allocator<BASE_STRUCT> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT * __thiscall
std::allocator<BASE_STRUCT>::allocate(allocator<BASE_STRUCT> *this,uint param_1)

{
  BASE_STRUCT *pBVar1;
  
  pBVar1 = _Allocate<BASE_STRUCT>(param_1,(BASE_STRUCT *)0x0);
  return pBVar1;
}
