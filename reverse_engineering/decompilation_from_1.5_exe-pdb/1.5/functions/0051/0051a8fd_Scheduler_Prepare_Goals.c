/*
 * Entry: 0051a8fd
 * Name: Scheduler::Prepare_Goals
 * Namespace: Scheduler
 * Signature: int Prepare_Goals(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Prepare_Goals(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  tag_sortlist *ptVar3;
  tag_c_linked_list *ptVar4;
  int *piVar5;
  float10 fVar6;
  
  if (this->goals_inited == 0) {
    ptVar1 = this->the_team->AIP;
    if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0xbb;
      tlog(0x800,"\n\nPreparing Goals %d");
    }
    this->min_priority = 1000000000.0;
    this->max_priority = -1000000000.0;
    piVar5 = this->goal_count;
    for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = 0;
      piVar5 = piVar5 + 1;
    }
    ptVar3 = Sortlist_New(this->new_goals->count);
    this->sorted_goals = ptVar3;
    iVar2 = this->new_goals->count;
    while (iVar2 = iVar2 + -1, -1 < iVar2) {
      piVar5 = C_Linked_List_Return_Data_By_Number(this->new_goals,iVar2);
      (**(code **)(*piVar5 + 4))();
      piVar5[8] = 0;
      if (piVar5[1] != 0) {
        fVar6 = (float10)(**(code **)(*piVar5 + 0x1c))();
        if (piVar5[1] != 0) {
          piVar5[7] = -0x319194d8;
          (**(code **)(*piVar5 + 0x14))();
          Sortlist_Add_Data(this->sorted_goals,piVar5,(double)fVar6);
        }
      }
      piVar5[6] = 0;
      if (piVar5[10] == 0) {
        C_Linked_List_Remove_Cell(this->new_goals,(tag_c_list_cell *)piVar5[0xd]);
      }
    }
    this->pos_in_sorted_goal_list = this->sorted_goals->count + -1;
    ptVar4 = C_Linked_List_New();
    this->good_matches = ptVar4;
    ptVar4 = C_Linked_List_New();
    this->valid_goals = ptVar4;
    ptVar1 = this->the_team->AIP;
    iVar2 = 0;
    if (((ptVar1 != (tagAIP_struct *)0x0) && (1 < ptVar1->VERBOSE_SCHEDULER)) &&
       (0 < this->sorted_goals->count)) {
      do {
        piVar5 = Sortlist_Return_Data_By_Number(this->sorted_goals,iVar2);
        (**(code **)(*piVar5 + 8))();
        _tlog_filename = ".\\Schedule\\scheduler.cpp";
        _tlog_line = 0x126;
        tlog(0x800,"    GOAL %d........P: %f   S: %d");
        iVar2 = iVar2 + 1;
      } while (iVar2 < this->sorted_goals->count);
    }
    iVar2 = 1;
    this->goals_inited = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}
