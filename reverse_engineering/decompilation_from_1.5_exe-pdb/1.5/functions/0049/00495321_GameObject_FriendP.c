/*
 * Entry: 00495321
 * Name: GameObject::FriendP
 * Namespace: GameObject
 * Signature: bool FriendP(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::FriendP(GameObject *this,int param_1)

{
  bool bVar1;
  
  if (((this->teamList != (Team *)0x0) && (-1 < param_1)) &&
     (bVar1 = Team::FriendP(this->teamList,param_1), bVar1)) {
    return true;
  }
  return false;
}
