/*
 * Entry: 0051b618
 * Name: Scheduler::Send_Groups_On_Missions
 * Namespace: Scheduler
 * Signature: void Send_Groups_On_Missions(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Send_Groups_On_Missions(Scheduler *this)

{
  int iVar1;
  tagAIP_struct *ptVar2;
  void *pvVar3;
  
  Squad_Check_Squad_List_Valid_Body(&this->the_team->my_squads,".\\Schedule\\scheduler.cpp",0x793);
  iVar1 = (this->the_team->my_squads).count;
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    pvVar3 = C_Linked_List_Return_Data_By_Number(&this->the_team->my_squads,iVar1);
    if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x28) != 0)) {
      (**(code **)(**(int **)((int)pvVar3 + 0x28) + 0x28))();
    }
    ptVar2 = this->the_team->AIP;
    if ((ptVar2 != (tagAIP_struct *)0x0) && (2 < ptVar2->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x7b3;
      tlog(0x800,"Sending group %d");
    }
  }
  Squad_Check_Squad_List_Valid_Body(&this->the_team->my_squads,".\\Schedule\\scheduler.cpp",0x7bb);
  this->send_groups_done = 1;
  return;
}
