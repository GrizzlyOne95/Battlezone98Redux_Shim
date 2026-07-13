/*
 * Entry: 0045dfe1
 * Name: GetMaxScrap
 * Namespace: Global
 * Signature: int GetMaxScrap(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMaxScrap(int param_1)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetMaxScrap(this);
  return lVar1;
}
