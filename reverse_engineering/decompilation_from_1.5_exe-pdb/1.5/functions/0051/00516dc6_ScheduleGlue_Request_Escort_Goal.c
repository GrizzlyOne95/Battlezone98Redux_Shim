/*
 * Entry: 00516dc6
 * Name: ScheduleGlue_Request_Escort_Goal
 * Namespace: Global
 * Signature: void ScheduleGlue_Request_Escort_Goal(Escort_Goal * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScheduleGlue_Request_Escort_Goal(Escort_Goal *param_1,int param_2)

{
  if (AI_map->team[param_2] != (tag_team *)0x0) {
    Scheduler::Add_Goal(AI_map->team[param_2]->scheduler,(Goal *)param_1);
  }
  return;
}
