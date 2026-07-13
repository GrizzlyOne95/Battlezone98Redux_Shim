/*
 * Entry: 00531195
 * Name: MachineGun::MachineGun
 * Namespace: MachineGun
 * Signature: MachineGun * MachineGun(MachineGun * this, _OBJ76 * param_1, MachineGunClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MachineGun * __thiscall
MachineGun::MachineGun(MachineGun *this,_OBJ76 *param_1,MachineGunClass *param_2)

{
  Cannon::Cannon((Cannon *)this,param_1,(CannonClass *)param_2);
  this->go = (_gas_object *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
