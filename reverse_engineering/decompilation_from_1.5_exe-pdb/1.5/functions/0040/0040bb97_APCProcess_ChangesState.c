/*
 * Entry: 0040bb97
 * Name: APCProcess::ChangesState
 * Namespace: APCProcess
 * Signature: bool ChangesState(APCProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall APCProcess::ChangesState(APCProcess *this,AiCommand param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  float fVar4;
  UnitMsg UVar5;
  
  if (param_1 == CMD_NONE) {
    if ((((*(int *)&this->field_0x18 != 0xb) &&
         (iVar3 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x2c + 0x20))(),
         *(int *)(iVar3 + 0x20) == 0x41504300)) &&
        (*(int *)(*(int *)&this->field_0x2c + 0x2c0) == 0)) &&
       (fVar4 = Get_Time(), *(float *)&this->field_0x48 + 1.0 < fVar4)) {
      GameObject::SetCommand(*(GameObject **)&this->field_0x2c,CMD_GET_RELOAD);
      piVar1 = (int *)(*(int *)&this->field_0x2c + 0xc4);
      *piVar1 = *piVar1 + 1;
      *(undefined4 *)&this->field_0x1c = 0xb;
      return true;
    }
  }
  else {
    if ((param_1 != CMD_SELECT) || (*(int *)&this->field_0x18 != 7)) {
      bVar2 = UnitProcess::ChangesState((UnitProcess *)this,param_1);
      return bVar2;
    }
    if ((*(int *)&this->field_0x30 == 0) || (*(int *)(*(int *)&this->field_0x30 + 0xc) != 5)) {
      UVar5 = SELECT_OTHER_MSG;
    }
    else {
      UVar5 = SELECT_DROPOFF_MSG;
    }
    Say(*(Craft **)&this->field_0x2c,UVar5,0);
    GameObject::GetWhat(*(GameObject **)&this->field_0x2c);
  }
  return false;
}
