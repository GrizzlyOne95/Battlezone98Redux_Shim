/*
 * Entry: 0051a2fa
 * Name: AISchedule_PreLoad
 * Namespace: Global
 * Signature: void AISchedule_PreLoad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_PreLoad(void)

{
  log_mode = log_mode & 0xffff35ff;
  tinfo.workdir[0] = '\0';
  tinfo.aipdir[0] = '\0';
  InitObjectClasses();
  Random_Init(0,0);
  AI_SpecialForcesInit();
  AI_AIPInit();
  memset(teamdata,0,0x1e80);
  Build_Init();
  Units_Init();
  return;
}
