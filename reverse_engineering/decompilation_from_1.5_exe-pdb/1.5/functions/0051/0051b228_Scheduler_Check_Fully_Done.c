/*
 * Entry: 0051b228
 * Name: Scheduler::Check_Fully_Done
 * Namespace: Scheduler
 * Signature: void Check_Fully_Done(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Check_Fully_Done(Scheduler *this)

{
  int iVar1;
  
  if ((-1 < this->pos_in_sorted_goal_list) &&
     (iVar1 = (this->the_team->my_units).count,
     iVar1 != this->allocated_troops && -1 < iVar1 - this->allocated_troops)) {
    Reset_Subschedule(this);
    return;
  }
  return;
}
