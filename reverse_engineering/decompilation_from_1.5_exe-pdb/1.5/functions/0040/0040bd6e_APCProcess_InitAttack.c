/*
 * Entry: 0040bd6e
 * Name: APCProcess::InitAttack
 * Namespace: APCProcess
 * Signature: void InitAttack(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::InitAttack(APCProcess *this)

{
  int iVar1;
  GameObject *pGVar2;
  APCAttack *pAVar3;
  
  iVar1 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x2c + 0x20))();
  if (*(int *)(iVar1 + 0x20) != 0x41504300) {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
  pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pAVar3 = operator_new(0x138);
  if (pAVar3 == (APCAttack *)0x0) {
    pAVar3 = (APCAttack *)0x0;
  }
  else {
    pAVar3 = APCAttack::APCAttack(pAVar3,*(Craft **)&this->field_0x2c,pGVar2);
  }
  *(APCAttack **)&this->field_0x30 = pAVar3;
  return;
}
