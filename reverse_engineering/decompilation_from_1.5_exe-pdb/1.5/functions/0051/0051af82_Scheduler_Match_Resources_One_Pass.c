/*
 * Entry: 0051af82
 * Name: Scheduler::Match_Resources_One_Pass
 * Namespace: Scheduler
 * Signature: void Match_Resources_One_Pass(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Match_Resources_One_Pass(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  tag_squad *ptVar2;
  undefined4 *puVar3;
  int iVar4;
  tag_c_list_cell *ptVar5;
  int iVar6;
  Scheduler *local_c;
  Scheduler *local_8;
  
  ptVar1 = this->the_team->AIP;
  iVar6 = (this->the_team->my_units).count - this->allocated_troops;
  local_c = this;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x36c;
    local_8 = this;
    tlog(0x800,"Start allocated_troops = %d");
  }
  local_8 = (Scheduler *)this->the_matches->count;
  while ((local_8 = (Scheduler *)((int)local_8 + -1), -1 < (int)local_8 && (0 < iVar6))) {
    puVar3 = Sortlist_Return_Data_By_Number(this->the_matches,(int)local_8);
    if ((puVar3 != (undefined4 *)0x0) &&
       (((iVar4 = puVar3[2], *(int *)(iVar4 + 0x18) == 0 &&
         (ptVar2 = (tag_squad *)puVar3[1], 0 < (ptVar2->my_units).count)) &&
        (iVar4 = *(int *)(iVar4 + 0xc) - *(int *)(iVar4 + 8), 0 < iVar4)))) {
      if (ptVar2->strength < iVar4) {
        iVar4 = ptVar2->strength;
      }
      iVar4 = Squad_Transfer_N_Appropriate_Strength_Points
                        (this->the_team,ptVar2,(tag_squad *)*puVar3,iVar4,(int *)&local_c,
                         (Goal *)puVar3[2]);
      if (0 < iVar4) {
        puVar3[3] = iVar4;
        *(int *)(puVar3[2] + 8) = *(int *)(puVar3[2] + 8) + iVar4;
        *(int *)(puVar3[1] + 0x20) = *(int *)(puVar3[1] + 0x20) + iVar4;
        iVar6 = iVar6 - (int)local_c;
        if (puVar3[8] == 0) {
          puVar3[8] = 1;
          ptVar5 = C_Linked_List_Add_Data(this->good_matches,puVar3);
          puVar3[9] = ptVar5;
        }
      }
    }
  }
  this->allocated_troops = (this->the_team->my_units).count - iVar6;
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x3d4;
    tlog(0x800,"End allocated_troops = %d.  @(%d, %d)");
  }
  return;
}
