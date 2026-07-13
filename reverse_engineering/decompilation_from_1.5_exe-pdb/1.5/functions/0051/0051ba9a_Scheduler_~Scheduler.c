/*
 * Entry: 0051ba9a
 * Name: Scheduler::~Scheduler
 * Namespace: Scheduler
 * Signature: void ~Scheduler(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::~Scheduler(Scheduler *this)

{
  Clean_Up(this);
  C_Linked_List_Delete(this->new_goals);
  C_Linked_List_Delete(this->goals_to_delete);
  return;
}
