/*
 * Entry: 00497689
 * Name: std::allocator<GameObject_*>::allocate
 * Namespace: std::allocator<GameObject_*>
 * Signature: GameObject * * allocate(allocator<GameObject_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::allocator<GameObject_*>::allocate(allocator<GameObject_*> *this,uint param_1)

{
  GameObject **ppGVar1;
  
  ppGVar1 = _Allocate<GameObject_*>(param_1,(GameObject **)0x0);
  return ppGVar1;
}
