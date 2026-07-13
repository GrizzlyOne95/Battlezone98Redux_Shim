/*
 * Entry: 004107b4
 * Name: RigProcess::ChangesState
 * Namespace: RigProcess
 * Signature: bool ChangesState(RigProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RigProcess::ChangesState(RigProcess *this,AiCommand param_1)

{
  Craft *this_00;
  bool bVar1;
  int iVar2;
  GameObject *this_01;
  UnitMsg UVar3;
  
  if (param_1 == CMD_NONE) {
    return false;
  }
  if (param_1 == CMD_SELECT) {
    if (*(int *)&this->field_0x18 != 0x10) {
      param_1 = CMD_SELECT;
LAB_004108c5:
      bVar1 = UnitProcess::ChangesState((UnitProcess *)this,param_1);
      return bVar1;
    }
    if (*(int *)(*(int *)&this->field_0x30 + 0x150) == 2) {
      UVar3 = SELECT_USER1_MSG;
    }
    else {
      UVar3 = SELECT_GO_MSG;
    }
  }
  else {
    if (param_1 == CMD_STOP) {
      Say(*(Craft **)&this->field_0x2c,OTHER_MSG,0);
      bVar1 = Producer::IsBusy(*(Producer **)&this->field_0x2c);
      if (bVar1) {
        *(undefined4 *)&this->field_0x40 = 0;
        Producer::CancelBuild(*(Producer **)&this->field_0x2c);
      }
      *(undefined4 *)&this->field_0x1c = 3;
      return true;
    }
    if (param_1 == CMD_DROPOFF) {
LAB_00410811:
      *(undefined4 *)&this->field_0x1c = 0x10;
      return true;
    }
    if (param_1 != CMD_NO_DROPOFF) {
      if (param_1 == CMD_RECYCLE) {
        this_00 = *(Craft **)&this->field_0x2c;
        iVar2 = GameObject::GetHandle((GameObject *)this_00);
        if (this_00->_padding_ == iVar2) {
          Say(this_00,RECYCLE_MSG,0);
          *(undefined4 *)&this->field_0x1c = 0xd;
        }
        else {
          Say(this_00,OTHER_MSG,0);
          *(undefined4 *)&this->field_0x1c = 0x11;
        }
        return true;
      }
      if (param_1 != CMD_BUILD) goto LAB_004108c5;
      Say(*(Craft **)&this->field_0x2c,OTHER_MSG,0);
      this_01 = *(GameObject **)&this->field_0x2c;
      *(long *)&this->field_0x40 = (this_01->nextCmd).param;
      if ((this_01->nextCmd).where != (AiPath *)0x0) goto LAB_00410811;
      goto LAB_0041081c;
    }
    UVar3 = SELECT_USER2_MSG;
  }
  Say(*(Craft **)&this->field_0x2c,UVar3,0);
  this_01 = *(GameObject **)&this->field_0x2c;
LAB_0041081c:
  GameObject::GetWhat(this_01);
  return false;
}
