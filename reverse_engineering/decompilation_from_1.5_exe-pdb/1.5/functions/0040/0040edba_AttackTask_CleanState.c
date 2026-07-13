/*
 * Entry: 0040edba
 * Name: AttackTask::CleanState
 * Namespace: AttackTask
 * Signature: void CleanState(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackTask::CleanState(AttackTask *this)

{
  int iVar1;
  
  switch(this->_padding_) {
  case 2:
  case 0xb:
  case 0xc:
    UnitTask::CleanGoto((UnitTask *)this);
    break;
  case 3:
    UnitTask::CleanStuck((UnitTask *)this);
    break;
  case 9:
    this->fleeFrom = 0;
  case 5:
  case 7:
  case 8:
  case 10:
    iVar1 = this->_padding_;
    if ((((iVar1 != 5) && (iVar1 != 7)) && (iVar1 != 8)) && ((iVar1 != 9 && (iVar1 != 10)))) {
      UnitTask::CleanSpecial((UnitTask *)this);
    }
  }
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  return;
}
