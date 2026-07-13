/*
 * Entry: 0052eb5e
 * Name: std::allocator<ExplosionClass_*>::allocate
 * Namespace: std::allocator<ExplosionClass_*>
 * Signature: ExplosionClass * * allocate(allocator<ExplosionClass_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __thiscall
std::allocator<ExplosionClass_*>::allocate(allocator<ExplosionClass_*> *this,uint param_1)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = _Allocate<ExplosionClass_*>(param_1,(ExplosionClass **)0x0);
  return ppEVar1;
}
