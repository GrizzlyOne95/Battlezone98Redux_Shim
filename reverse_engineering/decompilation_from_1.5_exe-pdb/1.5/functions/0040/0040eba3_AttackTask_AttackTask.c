/*
 * Entry: 0040eba3
 * Name: AttackTask::AttackTask
 * Namespace: AttackTask
 * Signature: AttackTask * AttackTask(AttackTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackTask * __thiscall AttackTask::AttackTask(AttackTask *this,Craft *param_1,GameObject *param_2)

{
  AttackGroup *this_00;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  this->_padding_ = (int)&_vftable_;
  if (param_2 == (GameObject *)0x0) {
    this->_padding_ = 0;
    this->_padding_ = 0xd;
    this->_padding_ = 0xd;
  }
  else {
    this_00 = AttackGroup::Find(param_2);
    this->_padding_ = (int)this_00;
    AttackGroup::Join(this_00,(GameObject *)param_1,(UnitTask *)this);
    this->_padding_ = 0x42200000;
    this->fleeFrom = 0;
    this->attackRangeSq = 102400.0;
    this->_padding_ = 1;
    this->waitRangeSq = 136900.0;
    this->_padding_ = 1;
    this->_padding_ = 0x3ca3d70a;
    this->_padding_ = this->_padding_;
    this->_padding_ = 0;
  }
  return this;
}
