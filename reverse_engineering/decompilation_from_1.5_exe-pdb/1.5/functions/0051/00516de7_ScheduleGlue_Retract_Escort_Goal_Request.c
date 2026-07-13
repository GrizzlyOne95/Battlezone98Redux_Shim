/*
 * Entry: 00516de7
 * Name: ScheduleGlue_Retract_Escort_Goal_Request
 * Namespace: Global
 * Signature: void ScheduleGlue_Retract_Escort_Goal_Request(Escort_Goal * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScheduleGlue_Retract_Escort_Goal_Request(Escort_Goal *param_1,int param_2)

{
  if (AI_map->team[param_2] != (tag_team *)0x0) {
    Scheduler::Remove_Goal(AI_map->team[param_2]->scheduler,(Goal *)param_1);
  }
  return;
}
