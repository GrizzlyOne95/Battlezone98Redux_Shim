/*
 * Entry: 00470249
 * Name: WingmanProcess::InitUState1
 * Namespace: WingmanProcess
 * Signature: void InitUState1(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::InitUState1(WingmanProcess *this)

{
  Craft *pCVar1;
  VEHICLE *pVVar2;
  AiPath *pAVar3;
  AiTask *pAVar4;
  
  pCVar1 = *(Craft **)&this->field_0x2c;
  pVVar2 = pCVar1->vhcl;
  pAVar3 = *(AiPath **)&this->field_0x38;
  (pVVar2->control).steer = 0.0;
  (pVVar2->control).pitch = 0.0;
  pAVar4 = HuntTask_Build(pCVar1,pAVar3);
  *(AiTask **)&this->field_0x30 = pAVar4;
  return;
}
