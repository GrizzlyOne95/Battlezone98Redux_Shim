/*
 * Entry: 0045dd9c
 * Name: Ally
 * Namespace: Global
 * Signature: void Ally(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ally(int param_1,int param_2)

{
  Team *pTVar1;
  
  pTVar1 = Team::GetTeam(param_1);
  if (pTVar1 != (Team *)0x0) {
    Team::Ally(pTVar1,param_2);
  }
  pTVar1 = Team::GetTeam(param_2);
  if (pTVar1 != (Team *)0x0) {
    Team::Ally(pTVar1,param_1);
  }
  Team_SetRelation(param_1,param_2,TR_ALLY);
  return;
}
