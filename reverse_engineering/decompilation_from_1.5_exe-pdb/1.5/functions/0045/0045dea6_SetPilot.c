/*
 * Entry: 0045dea6
 * Name: SetPilot
 * Namespace: Global
 * Signature: int SetPilot(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPilot(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetPilot(this);
  Team::AddPilot(this,param_2 - lVar1);
  lVar1 = Team::GetPilot(this);
  return lVar1;
}
