/*
 * Entry: 0051b9e1
 * Name: Scheduler::Allocate_Remaining_Troops
 * Namespace: Scheduler
 * Signature: void Allocate_Remaining_Troops(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Allocate_Remaining_Troops(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  
  if (((this->the_team->aicontrol != 0) && (iVar2 = Prepare_Goals(this), iVar2 != 1)) &&
     (iVar2 = Prepare_Squads(this), iVar2 != 1)) {
    Init_Subscheduling(this);
    iVar2 = Init_Precomputation(this);
    if (this->the_matches == (tag_sortlist *)0x0) {
      this->schedule_precompute_done = 1;
      this->schedule_matching_done = 1;
    }
    if (((iVar2 != 1) && (iVar2 = Precompute_Matches(this), iVar2 != 1)) &&
       ((iVar2 = Match_Resources(this), iVar2 != 1 && (iVar2 = Update_Squads(this), iVar2 != 1)))) {
      Clean_Up(this);
      ptVar1 = this->the_team->AIP;
      if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
        _tlog_filename = ".\\Schedule\\scheduler.cpp";
        _tlog_line = 0x772;
        tlog(0x800,"ALL DONE ALL DONE ALL DONE\n\n");
      }
      Fill_Last_Priorities(this);
      return;
    }
  }
  return;
}
