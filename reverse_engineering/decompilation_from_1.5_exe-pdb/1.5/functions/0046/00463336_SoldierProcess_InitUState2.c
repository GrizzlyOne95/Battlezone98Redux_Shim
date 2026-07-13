/*
 * Entry: 00463336
 * Name: SoldierProcess::InitUState2
 * Namespace: SoldierProcess
 * Signature: void InitUState2(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::InitUState2(SoldierProcess *this)

{
  GameObject *pGVar1;
  SoldierReturn *pSVar2;
  
  if (*(int *)&this->field_0x34 == 0) {
    pGVar1 = GameObject::GetObj(*(int *)(*(int *)&this->field_0x2c + 0x21c));
  }
  else {
    pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  }
  pSVar2 = operator_new(0x150);
  if (pSVar2 == (SoldierReturn *)0x0) {
    pSVar2 = (SoldierReturn *)0x0;
  }
  else {
    pSVar2 = SoldierReturn::SoldierReturn(pSVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(SoldierReturn **)&this->field_0x30 = pSVar2;
  return;
}
