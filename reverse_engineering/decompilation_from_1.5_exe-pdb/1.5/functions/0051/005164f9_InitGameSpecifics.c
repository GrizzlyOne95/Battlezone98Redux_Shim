/*
 * Entry: 005164f9
 * Name: InitGameSpecifics
 * Namespace: Global
 * Signature: void InitGameSpecifics(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGameSpecifics(void)

{
  int *piVar1;
  bool bVar2;
  Team *pTVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  TEAM_RELATION TVar8;
  
  PREREQ_Init();
  piVar4 = &teamdata[0].stats.kills_buildings;
  do {
    ((TEAM_STATS *)(piVar4 + -1))->kills_units = 0;
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    piVar4[3] = 0;
    piVar4[4] = 0;
    piVar4[5] = 0;
    piVar4[6] = 0;
    piVar4[7] = 0;
    piVar1 = piVar4 + 9;
    piVar4[8] = 0;
    piVar4 = piVar4 + 0x7a;
    *piVar1 = 0;
  } while ((int)piVar4 < 0xcd59b8);
  DR_AI_Init();
  iVar6 = 0;
  do {
    iVar5 = 0;
    do {
      iVar7 = iVar5;
      pTVar3 = Team::GetTeam(iVar6);
      bVar2 = Team::FriendP(pTVar3,iVar7);
      if (bVar2) {
        TVar8 = TR_ALLY;
      }
      else {
        iVar7 = iVar5;
        pTVar3 = Team::GetTeam(iVar6);
        bVar2 = Team::EnemyP(pTVar3,iVar7);
        if (bVar2) {
          TVar8 = TR_ENEMY;
        }
        else {
          TVar8 = TR_NEUTRAL;
        }
      }
      Team_SetRelation(iVar6,iVar5,TVar8);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10);
    AI_EnableTeam(iVar6);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x10);
  return;
}
