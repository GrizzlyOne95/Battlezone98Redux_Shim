/*
 * Entry: 0040f193
 * Name: AttackTask::InitState
 * Namespace: AttackTask
 * Signature: void InitState(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackTask::InitState(AttackTask *this)

{
  int iVar1;
  GameObject *pGVar2;
  int *piVar3;
  float fVar4;
  
  iVar1 = *(int *)(this->_padding_ + 0x228);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  switch(this->_padding_) {
  case 1:
    ChooseState(this);
    return;
  case 2:
  case 0xb:
  case 0xc:
    pGVar2 = GameObjectHandle::GetObj(this->_padding_);
    if (pGVar2 != (GameObject *)0x0) {
      piVar3 = (int *)(**(code **)(pGVar2->_padding_ + 0xc))();
      this->_padding_ = *piVar3;
      this->_padding_ = piVar3[1];
      this->_padding_ = piVar3[2];
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    this->_padding_ = (-(uint)(this->_padding_ != this->_padding_) & 0xfffffff4) + 0xd;
    break;
  case 3:
    UnitTask::InitStuck((UnitTask *)this);
    return;
  case 4:
    AssignFollowOffset(this);
    return;
  case 8:
  case 9:
  case 10:
    fVar4 = Get_Time();
    this->_padding_ = (int)fVar4;
  case 5:
  case 7:
    UnitTask::InitSpecial((UnitTask *)this);
    return;
  }
  return;
}
