/*
 * Entry: 005311b8
 * Name: MachineGun::~MachineGun
 * Namespace: MachineGun
 * Signature: void ~MachineGun(MachineGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MachineGun::~MachineGun(MachineGun *this)

{
  this->_padding_ = (int)&_vftable_;
  Cannon::~Cannon((Cannon *)this);
  return;
}
