/*
 * Entry: 005081a4
 * Name: DR_AI_Init
 * Namespace: Global
 * Signature: void DR_AI_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DR_AI_Init(void)

{
  uchar *puVar1;
  int iVar2;
  int *piVar3;
  
  tlog_gdm("AI::AI_Init Begins");
  Debug_Assert((uint)(ai_game_initialised == 0),0xe5,".\\Schedule\\Ai.cpp","!ai_game_initialised");
  ai_game_initialised = 1;
  AI_map = Strategy_Map_New((int)(mapsizex + 7 + (mapsizex + 7 >> 0x1f & 7U)) >> 3,
                            (int)(mapsizey + 7 + (mapsizey + 7 >> 0x1f & 7U)) >> 3,8);
  puVar1 = &teamdata[0].aicontrol;
  iVar2 = 0xcd3ab8;
  do {
    tlog_gdm("aicontrol[%d] = %d\n");
    iVar2 = iVar2 + 0x1e8;
  } while (iVar2 < 0xcd5938);
  AIBuild_Init();
  AI_Match_Init();
  Grassfire_Init(AI_map->AI_map_rows,AI_map->AI_map_columns);
  piVar3 = ai_team_enabled;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  iVar2 = 0;
  do {
    if (*puVar1 != '\0') {
      AI_InitTeam(iVar2);
    }
    puVar1 = puVar1 + 0x1e8;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < 0xcd5938);
  tlog_gdm("AI   All AI Teams created and units added\n");
  tlog_gdm("AI::AI_Init Ends");
  return;
}
