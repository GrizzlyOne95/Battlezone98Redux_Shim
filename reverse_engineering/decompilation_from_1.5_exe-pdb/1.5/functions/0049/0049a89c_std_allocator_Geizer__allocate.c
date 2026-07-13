/*
 * Entry: 0049a89c
 * Name: std::allocator<Geizer_*>::allocate
 * Namespace: std::allocator<Geizer_*>
 * Signature: Geizer * * allocate(allocator<Geizer_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __thiscall std::allocator<Geizer_*>::allocate(allocator<Geizer_*> *this,uint param_1)

{
  Geizer **ppGVar1;
  
  ppGVar1 = _Allocate<Geizer_*>(param_1,(Geizer **)0x0);
  return ppGVar1;
}
