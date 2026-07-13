/*
 * Entry: 005164c1
 * Name: PostScenarioLoadProcessing
 * Namespace: Global
 * Signature: void PostScenarioLoadProcessing(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PostScenarioLoadProcessing(void)

{
  int *piVar1;
  int *piVar2;
  
  PREREQ_Init();
  piVar2 = &teamdata[0].stats.kills_buildings;
  do {
    ((TEAM_STATS *)(piVar2 + -1))->kills_units = 0;
    *piVar2 = 0;
    piVar2[1] = 0;
    piVar2[2] = 0;
    piVar2[3] = 0;
    piVar2[4] = 0;
    piVar2[5] = 0;
    piVar2[6] = 0;
    piVar2[7] = 0;
    piVar1 = piVar2 + 9;
    piVar2[8] = 0;
    piVar2 = piVar2 + 0x7a;
    *piVar1 = 0;
  } while ((int)piVar2 < 0xcd59b8);
  return;
}
