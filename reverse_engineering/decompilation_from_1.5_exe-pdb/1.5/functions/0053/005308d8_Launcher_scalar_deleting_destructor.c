/*
 * Entry: 005308d8
 * Name: Launcher::`scalar_deleting_destructor'
 * Namespace: Launcher
 * Signature: void * `scalar_deleting_destructor'(Launcher * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Launcher::_scalar_deleting_destructor_(Launcher *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
