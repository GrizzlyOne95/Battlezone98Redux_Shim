/*
 * Entry: 0045df86
 * Name: GetScrap
 * Namespace: Global
 * Signature: int GetScrap(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetScrap(int param_1)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetScrap(this);
  return lVar1;
}
