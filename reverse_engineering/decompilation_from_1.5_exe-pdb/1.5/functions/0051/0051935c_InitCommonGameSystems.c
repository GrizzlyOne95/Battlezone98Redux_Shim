/*
 * Entry: 0051935c
 * Name: InitCommonGameSystems
 * Namespace: Global
 * Signature: void InitCommonGameSystems(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitCommonGameSystems(void)

{
  Random_Init(0,0);
  AI_SpecialForcesInit();
  AI_AIPInit();
  memset(teamdata,0,0x1e80);
  Build_Init();
  Units_Init();
  return;
}
