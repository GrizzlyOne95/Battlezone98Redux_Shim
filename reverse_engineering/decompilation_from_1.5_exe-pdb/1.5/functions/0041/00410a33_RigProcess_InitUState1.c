/*
 * Entry: 00410a33
 * Name: RigProcess::InitUState1
 * Namespace: RigProcess
 * Signature: void InitUState1(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::InitUState1(RigProcess *this)

{
  BuildGoto *pBVar1;
  
  Say(*(Craft **)&this->field_0x2c,USER1_MSG,0);
  pBVar1 = operator_new(0x15c);
  if (pBVar1 == (BuildGoto *)0x0) {
    pBVar1 = (BuildGoto *)0x0;
  }
  else {
    pBVar1 = BuildGoto::BuildGoto
                       (pBVar1,*(Craft **)&this->field_0x2c,*(AiPath **)&this->field_0x38,
                        *(GameObjectClass **)&this->field_0x40);
  }
  *(BuildGoto **)&this->field_0x30 = pBVar1;
  return;
}
