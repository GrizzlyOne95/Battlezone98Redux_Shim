/*
 * Entry: 0045df01
 * Name: SetMaxPilot
 * Namespace: Global
 * Signature: int SetMaxPilot(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetMaxPilot(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetMaxPilot(this);
  Team::AddMaxPilot(this,param_2 - lVar1);
  lVar1 = Team::GetMaxPilot(this);
  return lVar1;
}
