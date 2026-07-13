/*
 * Entry: 0051b5d6
 * Name: Scheduler::Planning_Status_Reset
 * Namespace: Scheduler
 * Signature: void Planning_Status_Reset(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Planning_Status_Reset(Scheduler *this)

{
  this->troop_allocation_done = 0;
  this->goals_inited = 0;
  this->squads_inited = 0;
  this->subscheduling_inited = 0;
  this->schedule_precompute_done = 0;
  this->precompute_inited = 0;
  this->schedule_matching_done = 0;
  this->schedule_squad_fix_done = 0;
  this->send_groups_done = 0;
  this->allocated_troops = 0;
  return;
}
