/*
 * Entry: 0045df97
 * Name: AddMaxScrap
 * Namespace: Global
 * Signature: int AddMaxScrap(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddMaxScrap(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  Team::AddMaxScrap(this,param_2);
  lVar1 = Team::GetMaxScrap(this);
  return lVar1;
}
