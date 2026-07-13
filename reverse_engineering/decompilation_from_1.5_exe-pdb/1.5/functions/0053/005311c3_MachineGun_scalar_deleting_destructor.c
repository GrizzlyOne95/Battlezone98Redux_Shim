/*
 * Entry: 005311c3
 * Name: MachineGun::`scalar_deleting_destructor'
 * Namespace: MachineGun
 * Signature: void * `scalar_deleting_destructor'(MachineGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MachineGun::_scalar_deleting_destructor_(MachineGun *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Cannon::~Cannon((Cannon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
