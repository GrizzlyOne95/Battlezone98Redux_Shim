/*
 * Entry: 004b1cbd
 * Name: Team::FriendP
 * Namespace: Team
 * Signature: bool FriendP(Team * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Team::FriendP(Team *this,int param_1)

{
  bool bVar1;
  
  if ((param_1 < 1) || ((this->dwAllies & 1 << ((byte)param_1 & 0x1f)) == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}
