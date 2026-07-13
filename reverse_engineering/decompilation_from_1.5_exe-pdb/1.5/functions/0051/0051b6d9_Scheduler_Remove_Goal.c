/*
 * Entry: 0051b6d9
 * Name: Scheduler::Remove_Goal
 * Namespace: Scheduler
 * Signature: void Remove_Goal(Scheduler * this, Goal * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Remove_Goal(Scheduler *this,Goal *param_1)

{
  C_Linked_List_Remove_Data(this->new_goals,param_1);
  if (param_1->invalid_goal != 0) {
    C_Linked_List_Add_Data(this->goals_to_delete,param_1);
  }
  return;
}
