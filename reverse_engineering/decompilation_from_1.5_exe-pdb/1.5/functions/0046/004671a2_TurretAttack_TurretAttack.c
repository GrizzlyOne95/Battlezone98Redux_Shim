/*
 * Entry: 004671a2
 * Name: TurretAttack::TurretAttack
 * Namespace: TurretAttack
 * Signature: TurretAttack * TurretAttack(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretAttack * __thiscall TurretAttack::TurretAttack(TurretAttack *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
