/*
 * Entry: 0045df2b
 * Name: GetMaxPilot
 * Namespace: Global
 * Signature: int GetMaxPilot(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMaxPilot(int param_1)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetMaxPilot(this);
  return lVar1;
}
