/*
 * Entry: 005082a1
 * Name: AI_Process
 * Namespace: Global
 * Signature: void AI_Process(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Process(void)

{
  tag_team *ptVar1;
  int iVar2;
  uchar *puVar3;
  int iVar4;
  
  tlog_gdm("AI::AI_Process Begins");
  iVar4 = 0;
  puVar3 = &teamdata[0].aicontrol;
  do {
    ptVar1 = AI_map->team[iVar4];
    if ((ptVar1 != (tag_team *)0x0) && (*puVar3 != '\0')) {
      iVar2 = AI_IsEnabled(ptVar1->team_ID);
      if ((iVar2 != 0) && (AI_map->team[iVar4]->AIP != (tagAIP_struct *)0x0)) {
        AI_Team_Update_Team_Strategy(AI_map,iVar4);
        AIBuild_TeamProcess(ptVar1);
      }
    }
    puVar3 = puVar3 + 0x1e8;
    iVar4 = iVar4 + 1;
  } while ((int)puVar3 < 0xcd5938);
  tlog_gdm("AI::AI_Process Ends");
  return;
}
