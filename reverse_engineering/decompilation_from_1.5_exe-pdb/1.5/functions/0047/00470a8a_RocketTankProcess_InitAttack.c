/*
 * Entry: 00470a8a
 * Name: RocketTankProcess::InitAttack
 * Namespace: RocketTankProcess
 * Signature: void InitAttack(RocketTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankProcess::InitAttack(RocketTankProcess *this)

{
  GameObject *pGVar1;
  RocketTankAttack *pRVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pRVar2 = operator_new(0x138);
  if (pRVar2 == (RocketTankAttack *)0x0) {
    pRVar2 = (RocketTankAttack *)0x0;
  }
  else {
    pRVar2 = RocketTankAttack::RocketTankAttack(pRVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(RocketTankAttack **)&this->field_0x30 = pRVar2;
  return;
}
