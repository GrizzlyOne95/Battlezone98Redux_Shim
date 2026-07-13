/*
 * Entry: 0051b0c3
 * Name: Scheduler::Free_Undercommitted_Troops
 * Namespace: Scheduler
 * Signature: int Free_Undercommitted_Troops(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Free_Undercommitted_Troops(Scheduler *this)

{
  float fVar1;
  tagAIP_struct *ptVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  void *pvVar6;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  tag_c_linked_list *local_8;
  
  fVar1 = 1e+09;
  pvVar6 = (void *)0x0;
  local_14 = 1;
  local_10 = 0;
  local_8 = C_Linked_List_New();
  local_c = 0;
  if (0 < this->good_matches->count) {
    do {
      pvVar3 = C_Linked_List_Return_Data_By_Number(this->good_matches,local_c);
      iVar4 = (**(code **)**(undefined4 **)((int)pvVar3 + 8))();
      if (iVar4 == 0) {
        *(undefined4 *)(*(int *)((int)pvVar3 + 8) + 0x18) = 1;
      }
      else {
        if (*(float *)(*(int *)((int)pvVar3 + 8) + 0x1c) < fVar1) {
          fVar1 = *(float *)(*(int *)((int)pvVar3 + 8) + 0x1c);
          C_Linked_List_Empty(local_8);
          pvVar6 = pvVar3;
        }
        if (*(int *)((int)pvVar6 + 8) == *(int *)((int)pvVar3 + 8)) {
          C_Linked_List_Add_Data(local_8,pvVar3);
        }
      }
      local_c = local_c + 1;
    } while (local_c < this->good_matches->count);
    if (pvVar6 != (void *)0x0) {
      local_14 = 0;
      *(undefined4 *)(*(int *)((int)pvVar6 + 8) + 0x18) = 1;
      ptVar2 = this->the_team->AIP;
      if ((ptVar2 != (tagAIP_struct *)0x0) && (2 < ptVar2->VERBOSE_SCHEDULER)) {
        _tlog_filename = ".\\Schedule\\scheduler.cpp";
        _tlog_line = 0x442;
        tlog(0x800,"SCHEDULER: Freeing goal ");
      }
      iVar4 = 0;
      if (0 < local_8->count) {
        do {
          puVar5 = C_Linked_List_Return_Data_By_Number(local_8,iVar4);
          Squad_Transfer_N_Strength_Points
                    (this->the_team,(tag_squad *)*puVar5,(tag_squad *)puVar5[1],
                     ((tag_squad *)*puVar5)->strength,&local_18);
          *(int *)(puVar5[2] + 8) = *(int *)(puVar5[2] + 8) - puVar5[3];
          *(int *)(puVar5[1] + 0x20) = *(int *)(puVar5[1] + 0x20) - puVar5[3];
          puVar5[3] = 0;
          local_10 = local_10 + local_18;
          C_Linked_List_Remove_Cell(this->good_matches,(tag_c_list_cell *)puVar5[9]);
          puVar5[8] = 0;
          iVar4 = iVar4 + 1;
        } while (iVar4 < local_8->count);
      }
    }
  }
  C_Linked_List_Delete(local_8);
  this->allocated_troops = this->allocated_troops - local_10;
  return local_14;
}
