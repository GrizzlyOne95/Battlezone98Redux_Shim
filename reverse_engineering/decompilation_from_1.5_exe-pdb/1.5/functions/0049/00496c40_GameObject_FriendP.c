/*
 * Entry: 00496c40
 * Name: GameObject::FriendP
 * Namespace: GameObject
 * Signature: bool FriendP(GameObject * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::FriendP(GameObject *this,GameObject *param_1)

{
  bool bVar1;
  int iVar2;
  
  if (param_1 != (GameObject *)0x0) {
    iVar2 = (**(code **)(param_1->_padding_ + 4))();
    bVar1 = FriendP(this,iVar2);
    if (bVar1) {
      return true;
    }
  }
  return false;
}
