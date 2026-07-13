/*
 * Entry: 0045de4d
 * Name: IsAlly
 * Namespace: Global
 * Signature: bool IsAlly(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsAlly(int param_1,int param_2)

{
  bool bVar1;
  GameObject *pGVar2;
  GameObject *this;
  int iVar3;
  
  pGVar2 = GameObject::GetObj(param_1);
  this = GameObject::GetObj(param_2);
  if ((pGVar2 == (GameObject *)0x0) || (this == (GameObject *)0x0)) {
    bVar1 = false;
  }
  else {
    iVar3 = (**(code **)(pGVar2->_padding_ + 4))();
    bVar1 = GameObject::FriendP(this,iVar3);
  }
  return bVar1;
}
