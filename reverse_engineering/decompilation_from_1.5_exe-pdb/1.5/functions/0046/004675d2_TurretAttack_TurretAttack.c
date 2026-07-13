/*
 * Entry: 004675d2
 * Name: TurretAttack::TurretAttack
 * Namespace: TurretAttack
 * Signature: TurretAttack * TurretAttack(TurretAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretAttack * __thiscall
TurretAttack::TurretAttack(TurretAttack *this,Craft *param_1,GameObject *param_2)

{
  AttackGroup *this_00;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  this->_padding_ = (int)&_vftable_;
  this_00 = AttackGroup::Find(param_2);
  this->_padding_ = (int)this_00;
  AttackGroup::Join(this_00,(GameObject *)param_1,(UnitTask *)this);
  this->_padding_ = 0x42200000;
  this->attackRangeSq = 102400.0;
  this->_padding_ = 1;
  this->_padding_ = 1;
  this->waitRangeSq = 136900.0;
  this->_padding_ = this->_padding_;
  this->_padding_ = 0;
  return this;
}
