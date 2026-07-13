/*
 * Entry: 0045dee1
 * Name: AddMaxPilot
 * Namespace: Global
 * Signature: int AddMaxPilot(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddMaxPilot(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  Team::AddMaxPilot(this,param_2);
  lVar1 = Team::GetMaxPilot(this);
  return lVar1;
}
