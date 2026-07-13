/*
 * Entry: 00499554
 * Name: std::allocator<GameObjectClass_*>::allocate
 * Namespace: std::allocator<GameObjectClass_*>
 * Signature: GameObjectClass * * allocate(allocator<GameObjectClass_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::allocator<GameObjectClass_*>::allocate(allocator<GameObjectClass_*> *this,uint param_1)

{
  GameObjectClass **ppGVar1;
  
  ppGVar1 = _Allocate<GameObjectClass_*>(param_1,(GameObjectClass **)0x0);
  return ppGVar1;
}
