/*
 * Entry: 00516450
 * Name: InitAIControl
 * Namespace: Global
 * Signature: void InitAIControl(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitAIControl(void)

{
  bool bVar1;
  Team *pTVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  TEAM_RELATION TVar6;
  
  DR_AI_Init();
  iVar4 = 0;
  do {
    iVar3 = 0;
    do {
      iVar5 = iVar3;
      pTVar2 = Team::GetTeam(iVar4);
      bVar1 = Team::FriendP(pTVar2,iVar5);
      if (bVar1) {
        TVar6 = TR_ALLY;
      }
      else {
        iVar5 = iVar3;
        pTVar2 = Team::GetTeam(iVar4);
        bVar1 = Team::EnemyP(pTVar2,iVar5);
        if (bVar1) {
          TVar6 = TR_ENEMY;
        }
        else {
          TVar6 = TR_NEUTRAL;
        }
      }
      Team_SetRelation(iVar4,iVar3,TVar6);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x10);
    AI_EnableTeam(iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  return;
}
