/*
 * Entry: 00450850
 * Name: std::allocator<Strip_*>::allocate
 * Namespace: std::allocator<Strip_*>
 * Signature: Strip * * allocate(allocator<Strip_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall std::allocator<Strip_*>::allocate(allocator<Strip_*> *this,uint param_1)

{
  Strip **ppSVar1;
  
  ppSVar1 = _Allocate<Strip_*>(param_1,(Strip **)0x0);
  return ppSVar1;
}
