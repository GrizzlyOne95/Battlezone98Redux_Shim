/*
 * Entry: 0051b241
 * Name: Scheduler::Match_Resources
 * Namespace: Scheduler
 * Signature: int Match_Resources(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Match_Resources(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  
  if (this->schedule_matching_done != 0) {
    return 0;
  }
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x4bb;
    tlog(0x800,"SCHEDULER: MATCHING RESOURCES.");
  }
  Match_Resources_One_Pass(this);
  iVar2 = Free_Undercommitted_Troops(this);
  if (iVar2 != 0) {
    this->schedule_matching_done = 1;
    Check_Fully_Done(this);
  }
  return 1;
}
