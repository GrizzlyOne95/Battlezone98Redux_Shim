/*
 * Entry: 00499a88
 * Name: GameObjectClass::Clean
 * Namespace: GameObjectClass
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObjectClass::Clean(void)

{
  uint uVar1;
  GameObjectClass **ppGVar2;
  
  uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppGVar2 = std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::back(&classList);
    if (*ppGVar2 != (GameObjectClass *)0x0) {
      (**(code **)(*ppGVar2)->_padding_)(1);
    }
    std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::pop_back(&classList);
    uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  }
  return;
}
