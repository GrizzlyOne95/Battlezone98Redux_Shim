/*
 * Entry: 0048b457
 * Name: std::allocator<BASE_STRUCT_*>::allocate
 * Namespace: std::allocator<BASE_STRUCT_*>
 * Signature: BASE_STRUCT * * allocate(allocator<BASE_STRUCT_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT ** __thiscall
std::allocator<BASE_STRUCT_*>::allocate(allocator<BASE_STRUCT_*> *this,uint param_1)

{
  BASE_STRUCT **ppBVar1;
  
  ppBVar1 = _Allocate<BASE_STRUCT_*>(param_1,(BASE_STRUCT **)0x0);
  return ppBVar1;
}
