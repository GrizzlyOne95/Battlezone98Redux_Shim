/*
 * Entry: 0052d784
 * Name: Dispenser::`scalar_deleting_destructor'
 * Namespace: Dispenser
 * Signature: void * `scalar_deleting_destructor'(Dispenser * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Dispenser::_scalar_deleting_destructor_(Dispenser *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
