/*
 * Entry: 00414f19
 * Name: GunTowerProcess::InitAttack
 * Namespace: GunTowerProcess
 * Signature: void InitAttack(GunTowerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerProcess::InitAttack(GunTowerProcess *this)

{
  GameObject *pGVar1;
  GunTowerAttack *pGVar2;
  
  (**(code **)(**(int **)&this->field_0x2c + 0x5c))();
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pGVar2 = operator_new(0x138);
  if (pGVar2 == (GunTowerAttack *)0x0) {
    pGVar2 = (GunTowerAttack *)0x0;
  }
  else {
    pGVar2 = GunTowerAttack::GunTowerAttack(pGVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(GunTowerAttack **)&this->field_0x30 = pGVar2;
  return;
}
