/*
 * Entry: 005108ce
 * Name: Goal::Goal
 * Namespace: Goal
 * Signature: Goal * Goal(Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Goal * __thiscall Goal::Goal(Goal *this)

{
  this->priority = 0.0;
  this->raw_priority = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->last_priority = 0.0;
  (this->the_troop_flow).strength = 0;
  (this->the_troop_flow).max_strength = 0;
  this->min_required_strength = 0;
  this->attacking_squad = (tag_squad *)0x0;
  this->dont_allocate = 0;
  this->removal_time = DONT_REMOVE;
  this->invalid_goal = 0;
  this->new_goal_cell_ptr = (tag_c_list_cell *)0x0;
  return this;
}
