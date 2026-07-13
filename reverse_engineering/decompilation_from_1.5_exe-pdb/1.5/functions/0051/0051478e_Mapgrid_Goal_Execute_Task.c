/*
 * Entry: 0051478e
 * Name: Mapgrid_Goal::Execute_Task
 * Namespace: Mapgrid_Goal
 * Signature: void Execute_Task(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mapgrid_Goal::Execute_Task(Mapgrid_Goal *this)

{
  if ((this->_padding_ == 0) &&
     (((this->_padding_ != 3 || (this->start_undercommitted_time == -1.0)) &&
      ((tag_squad *)this->_padding_ != (tag_squad *)0x0)))) {
    Squad_Send_Units(this->the_map,(tag_squad *)this->_padding_);
  }
  return;
}
