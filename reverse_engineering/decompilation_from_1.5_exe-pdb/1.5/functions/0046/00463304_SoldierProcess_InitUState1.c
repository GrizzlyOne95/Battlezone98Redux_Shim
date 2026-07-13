/*
 * Entry: 00463304
 * Name: SoldierProcess::InitUState1
 * Namespace: SoldierProcess
 * Signature: void InitUState1(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::InitUState1(SoldierProcess *this)

{
  GameObject *pGVar1;
  SoldierRetreat *pSVar2;
  GameObject *unaff_EDI;
  
  pGVar1 = FindBase(unaff_EDI);
  pSVar2 = operator_new(0x150);
  if (pSVar2 == (SoldierRetreat *)0x0) {
    pSVar2 = (SoldierRetreat *)0x0;
  }
  else {
    pSVar2 = SoldierRetreat::SoldierRetreat(pSVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(SoldierRetreat **)&this->field_0x30 = pSVar2;
  return;
}
