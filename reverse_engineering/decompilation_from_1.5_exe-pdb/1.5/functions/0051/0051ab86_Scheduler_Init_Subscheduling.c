/*
 * Entry: 0051ab86
 * Name: Scheduler::Init_Subscheduling
 * Namespace: Scheduler
 * Signature: void Init_Subscheduling(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Init_Subscheduling(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  local_8 = 0;
  bVar3 = false;
  if (this->subscheduling_inited == 0) {
    ptVar1 = this->the_team->AIP;
    if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x1c6;
      tlog(0x800,"Initing a subscheduling phase");
    }
    iVar6 = this->pos_in_sorted_goal_list;
    if (-1 < iVar6) {
      do {
        if (local_8 != 0) goto LAB_0051ad39;
        piVar4 = Sortlist_Return_Data_By_Number(this->sorted_goals,iVar6);
        iVar5 = piVar4[1];
        iVar2 = this->the_team->AIP->max_goals_of_type[iVar5];
        if ((iVar2 == -1) || (this->goal_count[iVar5] < iVar2)) {
          this->goal_count[iVar5] = this->goal_count[iVar5] + 1;
          iVar5 = (**(code **)(*piVar4 + 0xc))(&local_c);
          if (iVar5 == 0) {
            local_8 = 1;
            Squad_Detach_Goal((tag_squad *)piVar4[5]);
            piVar4[0xb] = 0;
          }
          else {
            if (((0 < local_c) && (ptVar1 = this->the_team->AIP, ptVar1 != (tagAIP_struct *)0x0)) &&
               (2 < ptVar1->VERBOSE_SCHEDULER)) {
              _tlog_filename = ".\\Schedule\\scheduler.cpp";
              _tlog_line = 0x1fb;
              tlog(0x800,"EXCESS TROOPS: Strength %d.");
            }
            if (piVar4[5] != 0) {
              *(undefined4 *)(piVar4[5] + 0x38) = 1;
            }
            piVar4[0xb] = 1;
            iVar6 = iVar6 + -1;
          }
        }
        else {
          iVar6 = iVar6 + -1;
          if ((tag_squad *)piVar4[5] != (tag_squad *)0x0) {
            Squad_Detach_Goal((tag_squad *)piVar4[5]);
          }
        }
      } while (-1 < iVar6);
      if (local_8 != 0) {
LAB_0051ad39:
        while ((-1 < iVar6 && (!bVar3))) {
          piVar4 = Sortlist_Return_Data_By_Number(this->sorted_goals,iVar6);
          iVar5 = piVar4[1];
          iVar2 = this->the_team->AIP->max_goals_of_type[iVar5];
          if ((iVar2 == -1) || (this->goal_count[iVar5] < iVar2)) {
            this->goal_count[iVar5] = this->goal_count[iVar5] + 1;
            iVar5 = (**(code **)(*piVar4 + 0xc))(&local_c);
            if (iVar5 == 0) {
              C_Linked_List_Append_Data(this->valid_goals,piVar4);
              Squad_Detach_Goal((tag_squad *)piVar4[5]);
              piVar4[0xb] = 0;
              iVar6 = iVar6 + -1;
            }
            else {
              bVar3 = true;
              piVar4[0xb] = 1;
            }
          }
          else {
            iVar6 = iVar6 + -1;
            if ((tag_squad *)piVar4[5] != (tag_squad *)0x0) {
              Squad_Detach_Goal((tag_squad *)piVar4[5]);
            }
          }
        }
      }
    }
    this->pos_in_sorted_goal_list = iVar6;
    this->subscheduling_inited = 1;
  }
  return;
}
