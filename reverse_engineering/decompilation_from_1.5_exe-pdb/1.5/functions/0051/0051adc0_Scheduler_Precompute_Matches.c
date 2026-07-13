/*
 * Entry: 0051adc0
 * Name: Scheduler::Precompute_Matches
 * Namespace: Scheduler
 * Signature: int Precompute_Matches(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Precompute_Matches(Scheduler *this)

{
  int *piVar1;
  tagAIP_struct *ptVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  int *piVar6;
  tag_squad *ptVar7;
  float10 fVar8;
  int local_c;
  int local_8;
  
  if (this->schedule_precompute_done == 0) {
    ptVar2 = this->the_team->AIP;
    if ((ptVar2 != (tagAIP_struct *)0x0) && (0 < ptVar2->VERBOSE_SCHEDULER)) {
      _tlog_filename = ".\\Schedule\\scheduler.cpp";
      _tlog_line = 0x2d2;
      tlog(0x800,"Pre-computing a match");
    }
    if (this->precompute_squad_number < (this->the_team->my_squads).count) {
      local_c = 0;
      do {
        if ((this->the_team->my_squads).count <= this->precompute_squad_number) break;
        pvVar4 = C_Linked_List_Return_Data_By_Number
                           (&this->the_team->my_squads,this->precompute_squad_number);
        if (((*(int *)((int)pvVar4 + 0x38) == 0) && (0 < *(int *)((int)pvVar4 + 0x14))) &&
           (local_8 = 0, 0 < this->valid_goals->count)) {
          do {
            piVar5 = C_Linked_List_Return_Data_By_Number(this->valid_goals,local_8);
            fVar8 = (float10)(**(code **)(*piVar5 + 0x18))();
            if (((float10)-5e+08 < fVar8) && (fVar8 < (float10)this->min_priority)) {
              this->min_priority = (double)fVar8;
            }
            if ((float10)this->max_priority < fVar8) {
              this->max_priority = (double)fVar8;
            }
            piVar6 = calloc(1,0x28);
            ptVar2 = this->the_team->AIP;
            if ((ptVar2 != (tagAIP_struct *)0x0) && (2 < ptVar2->VERBOSE_SCHEDULER)) {
              _tlog_filename = ".\\Schedule\\scheduler.cpp";
              _tlog_line = 0x310;
              tlog(0x800,"ALLOCATING match @%d");
            }
            piVar6[1] = (int)pvVar4;
            ptVar7 = Squad_New();
            *piVar6 = (int)ptVar7;
            ptVar7->resend = 1;
            *(int *)*piVar6 = this->the_team->max_squad_ID;
            piVar1 = &this->the_team->max_squad_ID;
            *piVar1 = *piVar1 + 1;
            *(tag_team **)(*piVar6 + 0x40) = this->the_team;
            *(double *)(piVar6 + 6) = (double)(float)fVar8;
            piVar6[3] = 0;
            piVar6[2] = (int)piVar5;
            iVar3 = *(int *)((int)pvVar4 + 0x34);
            piVar6[8] = 0;
            piVar6[4] = iVar3;
            Sortlist_Add_Data(this->the_matches,piVar6,(double)(float)fVar8);
            local_c = local_c + 1;
            local_8 = local_8 + 1;
          } while (local_8 < this->valid_goals->count);
        }
        this->precompute_squad_number = this->precompute_squad_number + 1;
      } while (local_c < 0x96);
      iVar3 = 1;
    }
    else {
      iVar3 = 1;
      this->schedule_precompute_done = 1;
    }
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}
