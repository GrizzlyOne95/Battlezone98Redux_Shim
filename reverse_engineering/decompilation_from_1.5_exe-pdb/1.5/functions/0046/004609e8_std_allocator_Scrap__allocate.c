/*
 * Entry: 004609e8
 * Name: std::allocator<Scrap_*>::allocate
 * Namespace: std::allocator<Scrap_*>
 * Signature: Scrap * * allocate(allocator<Scrap_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall std::allocator<Scrap_*>::allocate(allocator<Scrap_*> *this,uint param_1)

{
  Scrap **ppSVar1;
  
  ppSVar1 = _Allocate<Scrap_*>(param_1,(Scrap **)0x0);
  return ppSVar1;
}
