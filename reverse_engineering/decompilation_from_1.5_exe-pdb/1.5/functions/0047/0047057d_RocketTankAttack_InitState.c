/*
 * Entry: 0047057d
 * Name: RocketTankAttack::InitState
 * Namespace: RocketTankAttack
 * Signature: void InitState(RocketTankAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankAttack::InitState(RocketTankAttack *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0xc = 5;
  }
  else {
    if (iVar1 == 2) {
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
    if (iVar1 != 5) {
      return;
    }
  }
  *(undefined4 *)&this->field_0xf4 = 0x42960000;
  UnitTask::InitSpecial((UnitTask *)this);
  return;
}
