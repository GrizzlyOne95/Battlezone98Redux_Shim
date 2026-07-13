/*
 * Entry: 0044e2ca
 * Name: OffensiveProcess::InitWait
 * Namespace: OffensiveProcess
 * Signature: void InitWait(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::InitWait(OffensiveProcess *this)

{
  GameObject *pGVar1;
  bool bVar2;
  
  pGVar1 = GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
    (**(code **)(GameObject::userObject->_padding_ + 4))();
    (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
    bVar2 = GameObject::FriendP((GameObject *)this->_padding_,pGVar1);
    this->isFriend = bVar2;
  }
  UnitProcess::InitWait((UnitProcess *)this);
  return;
}
