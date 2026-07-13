/*
 * Entry: 0050eaac
 * Name: Escort_Goal::Escort_Goal
 * Namespace: Escort_Goal
 * Signature: Escort_Goal * Escort_Goal(Escort_Goal * this, ScavengerProcess * param_1, GameObject * param_2, int param_3, int param_4, float param_5, tag_strategy_map * param_6, tag_team * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Escort_Goal * __thiscall
Escort_Goal::Escort_Goal
          (Escort_Goal *this,ScavengerProcess *param_1,GameObject *param_2,int param_3,int param_4,
          float param_5,tag_strategy_map *param_6,tag_team *param_7)

{
  Goal::Goal((Goal *)this);
  this->requested_priority = param_5;
  this->damsels_ai_process = param_1;
  this->damsel_in_distress = param_2;
  this->min_escort_strength = param_3;
  this->max_escort_strength = param_4;
  this->the_map = param_6;
  this->the_team = param_7;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 1;
  this->_padding_ = 10;
  return this;
}
