/*
 * Entry: 0049272d
 * Name: std::allocator<GameFeature_*>::allocate
 * Namespace: std::allocator<GameFeature_*>
 * Signature: GameFeature * * allocate(allocator<GameFeature_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __thiscall
std::allocator<GameFeature_*>::allocate(allocator<GameFeature_*> *this,uint param_1)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = _Allocate<GameFeature_*>(param_1,(GameFeature **)0x0);
  return ppGVar1;
}
