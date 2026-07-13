/*
 * Entry: 0051ad4c
 * Name: Scheduler::Init_Precomputation
 * Namespace: Scheduler
 * Signature: int Init_Precomputation(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Scheduler::Init_Precomputation(Scheduler *this)

{
  tagAIP_struct *ptVar1;
  int iVar2;
  tag_sortlist *ptVar3;
  
  if (this->precompute_inited != 0) {
    return 0;
  }
  ptVar1 = this->the_team->AIP;
  if ((ptVar1 != (tagAIP_struct *)0x0) && (0 < ptVar1->VERBOSE_SCHEDULER)) {
    _tlog_filename = ".\\Schedule\\scheduler.cpp";
    _tlog_line = 0x28c;
    tlog(0x800,"Initializing the match lists");
  }
  iVar2 = this->valid_goals->count * (this->the_team->my_squads).count;
  if (iVar2 == 0) {
    this->the_matches = (tag_sortlist *)0x0;
  }
  else {
    ptVar3 = Sortlist_New(iVar2);
    this->precompute_squad_number = 0;
    this->the_matches = ptVar3;
  }
  this->precompute_inited = 1;
  return 1;
}
