/*
 * Entry: 0051a8a7
 * Name: Scheduler::Reset_Subschedule
 * Namespace: Scheduler
 * Signature: void Reset_Subschedule(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Reset_Subschedule(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x82;
    tlog(0x800,"RESET SUBSCHEDULE******************");
  }
  this->subscheduling_inited = 0;
  this->schedule_precompute_done = 0;
  this->precompute_inited = 0;
  this->schedule_matching_done = 0;
  this->schedule_squad_fix_done = 0;
  Subschedule_Clean_Up(this);
  return;
}
