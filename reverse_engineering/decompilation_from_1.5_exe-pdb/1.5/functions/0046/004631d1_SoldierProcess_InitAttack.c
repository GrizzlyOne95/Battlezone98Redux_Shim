/*
 * Entry: 004631d1
 * Name: SoldierProcess::InitAttack
 * Namespace: SoldierProcess
 * Signature: void InitAttack(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::InitAttack(SoldierProcess *this)

{
  GameObject *pGVar1;
  SoldierAttack *pSVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pSVar2 = operator_new(0x138);
  if (pSVar2 == (SoldierAttack *)0x0) {
    pSVar2 = (SoldierAttack *)0x0;
  }
  else {
    pSVar2 = SoldierAttack::SoldierAttack(pSVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(SoldierAttack **)&this->field_0x30 = pSVar2;
  return;
}
