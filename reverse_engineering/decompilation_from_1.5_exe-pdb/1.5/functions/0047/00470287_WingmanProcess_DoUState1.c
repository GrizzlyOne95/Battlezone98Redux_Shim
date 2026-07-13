/*
 * Entry: 00470287
 * Name: WingmanProcess::DoUState1
 * Namespace: WingmanProcess
 * Signature: void DoUState1(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::DoUState1(WingmanProcess *this)

{
  char cVar1;
  int iVar2;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if ((cVar1 != '\0') && (*(HuntTask **)&this->field_0x30 != (HuntTask *)0x0)) {
    iVar2 = HuntTask::Hunt_New_Spot(*(HuntTask **)&this->field_0x30);
    if (iVar2 == 0) {
      if (this->field_0x3c != '\0') {
        AiPath::Release(*(AiPath **)&this->field_0x38);
      }
      if (((*(GameObject **)&this->field_0x2c)->curCmd).what == CMD_GO) {
        GameObject::ClearCommand(*(GameObject **)&this->field_0x2c);
      }
      *(undefined4 *)&this->field_0x1c = 3;
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x004702d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
