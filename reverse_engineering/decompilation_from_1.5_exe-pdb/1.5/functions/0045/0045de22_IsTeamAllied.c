/*
 * Entry: 0045de22
 * Name: IsTeamAllied
 * Namespace: Global
 * Signature: bool IsTeamAllied(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsTeamAllied(int param_1,int param_2)

{
  bool bVar1;
  Team *this;
  
  if (((uint)param_1 < 0x10) && ((uint)param_2 < 0x10)) {
    this = Team::GetTeam(param_1);
    if (this != (Team *)0x0) {
      bVar1 = Team::FriendP(this,param_2);
      return bVar1;
    }
  }
  return false;
}
