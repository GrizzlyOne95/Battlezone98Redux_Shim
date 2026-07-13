/*
 * Entry: 0051b2ab
 * Name: Scheduler::Update_Squads
 * Namespace: Scheduler
 * Signature: int Update_Squads(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Update_Squads(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  int *piVar3;
  tag_c_list_cell *ptVar4;
  tag_squad *ptVar5;
  tag_c_linked_list *ptVar6;
  int local_8;
  Scheduler *local_4;
  
  if (this->schedule_squad_fix_done == 0) {
    ptVar1 = this->the_team->AIP;
    local_4 = this;
    if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x4f9;
      tlog(0x800,"Updating Squads");
    }
    Squad_Check_Squad_List_Valid_Body(&this->the_team->my_squads,".\\Schedule\\scheduler.cpp",0x4fd)
    ;
    local_8 = 0;
    if (0 < this->good_matches->count) {
      do {
        piVar3 = C_Linked_List_Return_Data_By_Number(this->good_matches,local_8);
        ptVar4 = C_Linked_List_Add_Data(&this->the_team->my_squads,(void *)*piVar3);
        *(tag_c_list_cell **)(*piVar3 + 0x44) = ptVar4;
        Squad_Check_Squad_List_Valid_Body
                  (&this->the_team->my_squads,".\\Schedule\\scheduler.cpp",0x50c);
        piVar3[8] = 1;
        ptVar5 = ((Goal *)piVar3[2])->attacking_squad;
        if (ptVar5 == (tag_squad *)0x0) {
          Squad_Set_Goal((tag_squad *)*piVar3,(Goal *)piVar3[2]);
          ptVar1 = this->the_team->AIP;
          if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\scheduler.cpp";
            _tlog_line = 0x520;
            tlog(0x800,"Using squad %d for goal");
          }
        }
        else {
          ptVar1 = this->the_team->AIP;
          if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
            _tlog_filename = ".\\Schedule\\scheduler.cpp";
            _tlog_line = 0x539;
            tlog(0x800,"Merging squad %d into squad %d.");
          }
          Squad_Transfer_N_Strength_Points
                    (this->the_team,(tag_squad *)*piVar3,ptVar5,((tag_squad *)*piVar3)->strength,
                     (int *)&local_4);
        }
        local_8 = local_8 + 1;
      } while (local_8 < this->good_matches->count);
    }
    iVar2 = (this->the_team->my_squads).count;
    while( true ) {
      ptVar6 = &this->the_team->my_squads;
      iVar2 = iVar2 + -1;
      if (iVar2 < 0) break;
      ptVar5 = C_Linked_List_Return_Data_By_Number(ptVar6,iVar2);
      if ((ptVar5->my_units).count < 1) {
        ptVar1 = this->the_team->AIP;
        if ((ptVar1 != (tagAIP_struct *)0x0) && (2 < ptVar1->VERBOSE_SCHEDULER)) {
          _tlog_filename = ".\\Schedule\\scheduler.cpp";
          _tlog_line = 0x55c;
          tlog(0x800,"Deleting SQUAD %d.");
        }
        C_Linked_List_Remove_Cell(&this->the_team->my_squads,ptVar5->my_squads_cell_ptr);
        Squad_Delete(ptVar5);
      }
    }
    Squad_Check_Squad_List_Valid_Body(ptVar6,".\\Schedule\\scheduler.cpp",0x56e);
    iVar2 = 1;
    this->schedule_squad_fix_done = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}
