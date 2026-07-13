/*
 * Entry: 005147c0
 * Name: Mapgrid_Goal::Mapgrid_Goal
 * Namespace: Mapgrid_Goal
 * Signature: Mapgrid_Goal * Mapgrid_Goal(Mapgrid_Goal * this, int param_1, int param_2, tag_strategy_map * param_3, tag_team * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Mapgrid_Goal * __thiscall
Mapgrid_Goal::Mapgrid_Goal
          (Mapgrid_Goal *this,int param_1,int param_2,tag_strategy_map *param_3,tag_team *param_4)

{
  Goal::Goal((Goal *)this);
  this->row = param_1;
  this->column = param_2;
  this->the_map = param_3;
  this->_padding_ = (int)&_vftable_;
  this->the_team = param_4;
  Clear_Goal(this);
  this->start_undercommitted_time = -1.0;
  this->_padding_ = 2;
  return this;
}
