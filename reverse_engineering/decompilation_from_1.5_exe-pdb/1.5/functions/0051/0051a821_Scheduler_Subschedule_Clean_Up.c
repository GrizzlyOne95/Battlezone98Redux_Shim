/*
 * Entry: 0051a821
 * Name: Scheduler::Subschedule_Clean_Up
 * Namespace: Scheduler
 * Signature: void Subschedule_Clean_Up(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Subschedule_Clean_Up(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  tag_squad_matching *ptVar2;
  int iVar3;
  
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x48;
    tlog(0x800,"Subschedule CLEAN-UP");
  }
  if (this->the_matches != (tag_sortlist *)0x0) {
    C_Linked_List_Empty(this->valid_goals);
    iVar3 = 0;
    if (0 < this->the_matches->count) {
      do {
        ptVar2 = Sortlist_Return_Data_By_Number(this->the_matches,iVar3);
        if (ptVar2->used == 0) {
          Squad_Matching_Delete(ptVar2);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < this->the_matches->count);
    }
    Sortlist_Delete(this->the_matches);
    this->the_matches = (tag_sortlist *)0x0;
  }
  return;
}
