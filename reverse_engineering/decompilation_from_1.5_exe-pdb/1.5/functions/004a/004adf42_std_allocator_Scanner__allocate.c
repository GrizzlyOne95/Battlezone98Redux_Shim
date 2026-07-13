/*
 * Entry: 004adf42
 * Name: std::allocator<Scanner_*>::allocate
 * Namespace: std::allocator<Scanner_*>
 * Signature: Scanner * * allocate(allocator<Scanner_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __thiscall std::allocator<Scanner_*>::allocate(allocator<Scanner_*> *this,uint param_1)

{
  Scanner **ppSVar1;
  
  ppSVar1 = _Allocate<Scanner_*>(param_1,(Scanner **)0x0);
  return ppSVar1;
}
