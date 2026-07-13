/*
 * Entry: 0051aa85
 * Name: Scheduler::Prepare_Squads
 * Namespace: Scheduler
 * Signature: int Prepare_Squads(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Prepare_Squads(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  tag_squad *ptVar3;
  int iVar4;
  char *pcVar5;
  
  iVar4 = 0;
  if (this->squads_inited == 0) {
    ptVar1 = this->the_team->AIP;
    if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x155;
      tlog(0x800,"Preparing all squads for scheduling");
    }
    if (0 < (this->the_team->my_squads).count) {
      do {
        ptVar3 = C_Linked_List_Return_Data_By_Number(&this->the_team->my_squads,iVar4);
        Squad_Compute_Location(ptVar3);
        iVar2 = (ptVar3->my_units).count;
        (ptVar3->the_troop_flow).strength = 0;
        (ptVar3->the_troop_flow).max_strength = iVar2;
        ptVar3->already_committed = 0;
        ptVar3->resend = 0;
        ptVar1 = this->the_team->AIP;
        if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          if (ptVar3->my_strategic_goal == (Goal *)0x0) {
            _tlog_line = 0x179;
            pcVar5 = "SQUAD %d...(%d, %d).....U: %d    Str: %d  --------";
          }
          else {
            _tlog_line = 0x18b;
            pcVar5 = "SQUAD %d (%d, %d)........U: %d    Str: %d  ";
          }
          tlog(0x800,pcVar5);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < (this->the_team->my_squads).count);
    }
    iVar4 = 1;
    this->squads_inited = 1;
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}
