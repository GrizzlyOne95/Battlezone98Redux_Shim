/*
 * Entry: 0051b702
 * Name: Scheduler::Scheduler
 * Namespace: Scheduler
 * Signature: Scheduler * Scheduler(Scheduler * this, tag_strategy_map * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scheduler * __thiscall
Scheduler::Scheduler(Scheduler *this,tag_strategy_map *param_1,tag_team *param_2)

{
  tag_c_linked_list *ptVar1;
  
  this->the_matches = (tag_sortlist *)0x0;
  this->good_matches = (tag_c_linked_list *)0x0;
  this->valid_goals = (tag_c_linked_list *)0x0;
  this->sorted_goals = (tag_sortlist *)0x0;
  ptVar1 = C_Linked_List_New();
  this->new_goals = ptVar1;
  ptVar1 = C_Linked_List_New();
  this->pos_in_sorted_goal_list = -1;
  this->min_priority = 1000000000.0;
  this->goals_to_delete = ptVar1;
  this->max_priority = -1000000000.0;
  this->the_team = param_2;
  this->max_last_priority = 0.0;
  this->min_last_priority = 0.0;
  this->the_map = param_1;
  Planning_Status_Reset(this);
  return this;
}
