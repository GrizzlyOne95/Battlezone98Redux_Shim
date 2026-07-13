/*
 * Entry: 0045de86
 * Name: AddPilot
 * Namespace: Global
 * Signature: int AddPilot(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddPilot(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  Team::AddPilot(this,param_2);
  lVar1 = Team::GetPilot(this);
  return lVar1;
}
