/*
 * Entry: 00412f02
 * Name: GechProcess::InitAttack
 * Namespace: GechProcess
 * Signature: void InitAttack(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechProcess::InitAttack(GechProcess *this)

{
  GameObject *pGVar1;
  GechAttack *pGVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pGVar2 = operator_new(0x138);
  if (pGVar2 == (GechAttack *)0x0) {
    pGVar2 = (GechAttack *)0x0;
  }
  else {
    pGVar2 = GechAttack::GechAttack(pGVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(GechAttack **)&this->field_0x30 = pGVar2;
  return;
}
