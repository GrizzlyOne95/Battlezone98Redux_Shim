/*
 * Entry: 00467a1d
 * Name: TurretAttack::~TurretAttack
 * Namespace: TurretAttack
 * Signature: void ~TurretAttack(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretAttack::~TurretAttack(TurretAttack *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  this->_padding_ = 0xd;
  if ((AttackGroup *)this->_padding_ != (AttackGroup *)0x0) {
    AttackGroup::Leave((AttackGroup *)this->_padding_,(GameObject *)this->_padding_);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
