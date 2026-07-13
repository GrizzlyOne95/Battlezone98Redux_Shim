/*
 * Entry: 0051691d
 * Name: AISchedule_SwitchAIP
 * Namespace: Global
 * Signature: void AISchedule_SwitchAIP(int param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_SwitchAIP(int param_1,void *param_2)

{
  if (AI_map->team[param_1] != (tag_team *)0x0) {
    AI_AIPSwitch(param_1,param_2);
  }
  return;
}
