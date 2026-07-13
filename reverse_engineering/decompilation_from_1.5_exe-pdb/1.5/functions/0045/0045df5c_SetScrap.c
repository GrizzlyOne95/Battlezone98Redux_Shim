/*
 * Entry: 0045df5c
 * Name: SetScrap
 * Namespace: Global
 * Signature: int SetScrap(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetScrap(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetScrap(this);
  Team::AddScrap(this,param_2 - lVar1);
  lVar1 = Team::GetScrap(this);
  return lVar1;
}
