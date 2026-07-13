/*
 * Entry: 0051689d
 * Name: AISchedule_AddScrap
 * Namespace: Global
 * Signature: void AISchedule_AddScrap(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_AddScrap(int param_1,int param_2)

{
  if (((AI_map != (tag_strategy_map *)0x0) && (-1 < param_2)) &&
     (teamdata[param_1].aicontrol != '\0')) {
    Team_ChangeCredits(param_1,param_2);
    AI_UnspentCreditAdd(param_1,param_2);
    return;
  }
  return;
}
