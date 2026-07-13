/*
 * Entry: 00468093
 * Name: TurretAttack::InitState
 * Namespace: TurretAttack
 * Signature: void InitState(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretAttack::InitState(TurretAttack *this)

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
  iVar1 = this->_padding_;
  if (iVar1 < 6) {
    if (iVar1 == 5) {
      UnitTask::InitSpecial((UnitTask *)this);
      return;
    }
    if (iVar1 == 1) {
      ChooseState(this);
      return;
    }
    if (iVar1 == 2) {
LAB_004680f8:
      pGVar2 = GameObjectHandle::GetObj(this->_padding_);
      piVar3 = (int *)(**(code **)(pGVar2->_padding_ + 0xc))();
      this->_padding_ = *piVar3;
      this->_padding_ = piVar3[1];
      this->_padding_ = piVar3[2];
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
    if (iVar1 == 4) {
      AssignFollowOffset(this);
      return;
    }
  }
  else if ((iVar1 == 8) || (iVar1 == 10)) {
    fVar4 = Get_Time();
    this->_padding_ = (int)fVar4;
  }
  else if (iVar1 - 0xbU < 2) goto LAB_004680f8;
  return;
}
