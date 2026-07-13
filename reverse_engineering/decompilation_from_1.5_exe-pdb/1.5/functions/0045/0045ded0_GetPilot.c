/*
 * Entry: 0045ded0
 * Name: GetPilot
 * Namespace: Global
 * Signature: int GetPilot(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPilot(int param_1)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetPilot(this);
  return lVar1;
}
