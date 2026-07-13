/*
 * Entry: 00498505
 * Name: GameObject_Clean
 * Namespace: Global
 * Signature: void GameObject_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_Clean(void)

{
  vector<GameObject_*,std::allocator<GameObject_*>_> *this;
  int iVar1;
  GameObject **ppGVar2;
  
  this = GameObject::objectList;
  iVar1 = (int)GameObject::objectList->_Mylast - (int)GameObject::objectList->_Myfirst >> 2;
  if (0 < iVar1) {
    do {
      ppGVar2 = std::vector<GameObject_*,std::allocator<GameObject_*>_>::back(this);
      (**(code **)((*ppGVar2)->_padding_ + 0x10))();
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}
