/*
 * Entry: 0051b4a3
 * Name: Scheduler::Report
 * Namespace: Scheduler
 * Signature: void Report(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Report(Scheduler *this)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  
  ptVar1 = this->the_team;
  iVar2 = 0;
  if (((ptVar1->AIP != (tagAIP_struct *)0x0) && (2 < ptVar1->AIP->VERBOSE_SCHEDULER)) &&
     (0 < (ptVar1->strategic_targets).grid_rows)) {
    do {
      iVar3 = 0;
      if (0 < (ptVar1->strategic_targets).grid_columns) {
        do {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          _tlog_line = 0x597;
          tlog(0x800,"Grid [%d, %d] %lf ");
          iVar3 = iVar3 + 1;
        } while (iVar3 < (this->the_team->strategic_targets).grid_columns);
      }
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x59c;
      tlog(0x800,"\n");
      ptVar1 = this->the_team;
      iVar2 = iVar2 + 1;
    } while (iVar2 < (ptVar1->strategic_targets).grid_rows);
  }
  return;
}
