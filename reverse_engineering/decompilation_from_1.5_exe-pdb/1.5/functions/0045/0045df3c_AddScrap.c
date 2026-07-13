/*
 * Entry: 0045df3c
 * Name: AddScrap
 * Namespace: Global
 * Signature: int AddScrap(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddScrap(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  Team::AddScrap(this,param_2);
  lVar1 = Team::GetScrap(this);
  return lVar1;
}
