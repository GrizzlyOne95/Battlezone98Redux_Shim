/*
 * Entry: 0045eb88
 * Name: GetTeamSlot
 * Namespace: Global
 * Signature: int GetTeamSlot(TEAM_SLOT param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTeamSlot(TEAM_SLOT param_1,int param_2)

{
  Team *this;
  GameObject *this_00;
  int iVar1;
  
  this = Team::GetTeam(param_2);
  this_00 = Team::GetSlot(this,param_1);
  if (this_00 == (GameObject *)0x0) {
    return 0;
  }
  iVar1 = GameObject::GetHandle(this_00);
  return iVar1;
}
