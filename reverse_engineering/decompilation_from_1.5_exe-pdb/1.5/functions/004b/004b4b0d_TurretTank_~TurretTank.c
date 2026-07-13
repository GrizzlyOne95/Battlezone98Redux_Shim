/*
 * Entry: 004b4b0d
 * Name: TurretTank::~TurretTank
 * Namespace: TurretTank
 * Signature: void ~TurretTank(TurretTank * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::~TurretTank(TurretTank *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
