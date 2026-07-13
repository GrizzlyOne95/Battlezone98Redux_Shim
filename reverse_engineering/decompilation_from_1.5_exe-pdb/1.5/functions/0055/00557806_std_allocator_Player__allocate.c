/*
 * Entry: 00557806
 * Name: std::allocator<Player_*>::allocate
 * Namespace: std::allocator<Player_*>
 * Signature: Player * * allocate(allocator<Player_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall std::allocator<Player_*>::allocate(allocator<Player_*> *this,uint param_1)

{
  Player **ppPVar1;
  
  ppPVar1 = _Allocate<Player_*>(param_1,(Player **)0x0);
  return ppPVar1;
}
