/*
 * Entry: 0051b6c2
 * Name: Scheduler::Add_Goal
 * Namespace: Scheduler
 * Signature: void Add_Goal(Scheduler * this, Goal * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Add_Goal(Scheduler *this,Goal *param_1)

{
  tag_c_list_cell *ptVar1;
  
  ptVar1 = C_Linked_List_Add_Data(this->new_goals,param_1);
  param_1->new_goal_cell_ptr = ptVar1;
  return;
}
