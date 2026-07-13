/*
 * Entry: 0051b765
 * Name: Scheduler::Clean_Up
 * Namespace: Scheduler
 * Signature: void Clean_Up(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Clean_Up(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  tag_squad_matching *ptVar2;
  Goal *this_00;
  int iVar3;
  
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x66a;
    tlog(0x800,"Scheduler CLEAN-UP");
  }
  if (this->sorted_goals != (tag_sortlist *)0x0) {
    Sortlist_Delete(this->sorted_goals);
    this->sorted_goals = (tag_sortlist *)0x0;
  }
  if (this->valid_goals != (tag_c_linked_list *)0x0) {
    C_Linked_List_Delete(this->valid_goals);
    this->valid_goals = (tag_c_linked_list *)0x0;
  }
  if (this->the_matches != (tag_sortlist *)0x0) {
    iVar3 = 0;
    if (0 < this->the_matches->count) {
      do {
        ptVar2 = Sortlist_Return_Data_By_Number(this->the_matches,iVar3);
        ptVar1 = this->the_team->AIP;
        if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          _tlog_line = 0x68f;
          tlog(0x800,"The Match Contains @%d\n");
        }
        if (ptVar2->used == 0) {
          Squad_Matching_Delete(ptVar2);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < this->the_matches->count);
    }
    Sortlist_Delete(this->the_matches);
    this->the_matches = (tag_sortlist *)0x0;
  }
  if (this->good_matches != (tag_c_linked_list *)0x0) {
    iVar3 = 0;
    if (0 < this->good_matches->count) {
      do {
        ptVar2 = C_Linked_List_Return_Data_By_Number(this->good_matches,iVar3);
        ptVar1 = this->the_team->AIP;
        if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          _tlog_line = 0x6b0;
          tlog(0x800,"GOOD Match Contains @%d\n");
        }
        if (ptVar2 == (tag_squad_matching *)0x0) {
          ptVar1 = this->the_team->AIP;
          if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\scheduler.cpp";
            _tlog_line = 0x6cf;
            tlog(0x800,"Good Matches list contains NULL match");
          }
        }
        else {
          if (this->schedule_squad_fix_done == 0) {
            Squad_Delete(ptVar2->transfer_units);
            ptVar2->transfer_units = (tag_squad *)0x0;
          }
          Squad_Matching_Delete(ptVar2);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < this->good_matches->count);
    }
    C_Linked_List_Delete(this->good_matches);
    this->good_matches = (tag_c_linked_list *)0x0;
  }
  if (this->goals_to_delete != (tag_c_linked_list *)0x0) {
    iVar3 = 0;
    if (0 < this->goals_to_delete->count) {
      do {
        this_00 = C_Linked_List_Return_Data_By_Number(this->goals_to_delete,iVar3);
        ptVar1 = this->the_team->AIP;
        if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          _tlog_line = 0x6e9;
          tlog(0x800,"Deleting goal @%d\n");
        }
        if (this_00 == (Goal *)0x0) {
          ptVar1 = this->the_team->AIP;
          if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\scheduler.cpp";
            _tlog_line = 0x704;
            tlog(0x800,"the_goal list contains NULL goal");
          }
        }
        else {
          if (this_00->attacking_squad != (tag_squad *)0x0) {
            Squad_Detach_Goal(this_00->attacking_squad);
          }
          Goal::~Goal(this_00);
          operator_delete(this_00);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < this->goals_to_delete->count);
    }
    C_Linked_List_Empty(this->goals_to_delete);
  }
  this->troop_allocation_done = 1;
  return;
}
