/*
 * Entry: 004b4d09
 * Name: TurretTank::TurretTank
 * Namespace: TurretTank
 * Signature: TurretTank * TurretTank(TurretTank * this, _OBJ76 * param_1, TurretTankClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTank * __thiscall
TurretTank::TurretTank(TurretTank *this,_OBJ76 *param_1,TurretTankClass *param_2)

{
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->delayTimer = -1e+30;
  this->animHandle = -1;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->_padding_ = 0;
  this->change_state = 0;
  this->turretYObj = (_OBJ76 *)0x0;
  this->turretXCount = 0;
  FindTurret(this,(_OBJ76 *)this->_padding_);
  this->prevYaw = 0.0;
  this->turretAligned = true;
  if (this->_padding_ != 0) {
    *(undefined4 *)(this->_padding_ + 0x34) = 0;
  }
  this->hazardTeam = 0;
  return this;
}
