/*
 * Entry: 00510900
 * Name: Goal::~Goal
 * Namespace: Goal
 * Signature: void ~Goal(Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Goal::~Goal(Goal *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->attacking_squad != (tag_squad *)0x0) {
    Squad_Detach_Goal(this->attacking_squad);
  }
  return;
}
