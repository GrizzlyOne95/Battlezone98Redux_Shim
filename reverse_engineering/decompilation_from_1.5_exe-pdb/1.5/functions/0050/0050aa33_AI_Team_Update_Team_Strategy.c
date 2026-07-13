/*
 * Entry: 0050aa33
 * Name: AI_Team_Update_Team_Strategy
 * Namespace: Global
 * Signature: void AI_Team_Update_Team_Strategy(tag_strategy_map * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Update_Team_Strategy(tag_strategy_map *param_1,int param_2)

{
  tag_team *ptVar1;
  tagAIP_struct *ptVar2;
  
  ptVar1 = param_1->team[param_2];
  if (((unitcycles & 0xf) == param_2) &&
     (ptVar2 = ptVar1->AIP,
     ptVar2->recompute_strategy_period <= (int)(unitcycles - ptVar2->last_strategy_unitcycles))) {
    if ((ptVar1->strategic_targets).compute_mapgrid == 0) {
      if ((ptVar2 != (tagAIP_struct *)0x0) && (0 < ptVar2->VERBOSE_SCHEDULER)) {
        _tlog_filename = ".\\Schedule\\ai_team.cpp";
        _tlog_line = 0x5cd;
        tlog(0x800,"AI_Team_Compute_Mapgrid.");
      }
      if (ptVar1->aicontrol != 0) {
        AI_Team_Compute_Mapgrid(param_1,ptVar1);
      }
      (ptVar1->strategic_targets).compute_mapgrid = 1;
    }
    else {
      if ((ptVar1->my_units).count == 0) {
        ptVar2->last_strategy_unitcycles = unitcycles;
        Scheduler::Clean_Up(ptVar1->scheduler);
        Scheduler::Planning_Status_Reset(ptVar1->scheduler);
        return;
      }
      if ((ptVar1->strategic_targets).squad_update_done == 0) {
        if ((ptVar2 != (tagAIP_struct *)0x0) && (0 < ptVar2->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\ai_team.cpp";
          _tlog_line = 0x607;
          tlog(0x800,"AI_Team_Update_Squads.");
        }
        AI_Team_Update_Squads(param_1,ptVar1);
        (ptVar1->strategic_targets).squad_update_done = 1;
      }
      else {
        if (ptVar1->scheduler->troop_allocation_done == 0) {
          if ((ptVar2 != (tagAIP_struct *)0x0) && (0 < ptVar2->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\ai_team.cpp";
            _tlog_line = 0x632;
            tlog(0x800,"the_team->scheduler->Allocate_Remaining_Troops.");
          }
          Scheduler::Allocate_Remaining_Troops(ptVar1->scheduler);
          return;
        }
        if (ptVar1->scheduler->send_groups_done == 0) {
          if ((ptVar2 != (tagAIP_struct *)0x0) && (0 < ptVar2->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\ai_team.cpp";
            _tlog_line = 0x646;
            tlog(0x800,"the_team->scheduler->Send_Groups_On_Missions.");
          }
          AI_Team_Clear_Missions(ptVar1);
          AI_Team_Print_Goals(ptVar1);
          Scheduler::Send_Groups_On_Missions(ptVar1->scheduler);
          return;
        }
        ptVar2->last_strategy_unitcycles = unitcycles;
        Scheduler::Planning_Status_Reset(ptVar1->scheduler);
        AI_Team_Planning_Status_Reset(ptVar1);
        AI_Team_Update_Rapid_Defenses(ptVar1);
      }
    }
  }
  return;
}
