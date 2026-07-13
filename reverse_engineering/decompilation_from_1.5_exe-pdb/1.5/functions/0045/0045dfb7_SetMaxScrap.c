/*
 * Entry: 0045dfb7
 * Name: SetMaxScrap
 * Namespace: Global
 * Signature: int SetMaxScrap(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetMaxScrap(int param_1,int param_2)

{
  Team *this;
  long lVar1;
  
  this = Team::GetTeam(param_1);
  lVar1 = Team::GetMaxScrap(this);
  Team::AddMaxScrap(this,param_2 - lVar1);
  lVar1 = Team::GetMaxScrap(this);
  return lVar1;
}
