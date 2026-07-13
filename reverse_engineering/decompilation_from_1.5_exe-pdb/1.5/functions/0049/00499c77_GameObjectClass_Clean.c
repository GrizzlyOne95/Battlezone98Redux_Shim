/*
 * Entry: 00499c77
 * Name: GameObjectClass_Clean
 * Namespace: Global
 * Signature: void GameObjectClass_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObjectClass_Clean(void)

{
  uint uVar1;
  GameObjectClass **ppGVar2;
  
  uVar1 = (int)GameObjectClass::classList._Mylast - (int)GameObjectClass::classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppGVar2 = std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::back
                        (&GameObjectClass::classList);
    if (*ppGVar2 != (GameObjectClass *)0x0) {
      (**(code **)(*ppGVar2)->_padding_)(1);
    }
    std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::pop_back
              (&GameObjectClass::classList);
    uVar1 = (int)GameObjectClass::classList._Mylast - (int)GameObjectClass::classList._Myfirst;
  }
  return;
}
