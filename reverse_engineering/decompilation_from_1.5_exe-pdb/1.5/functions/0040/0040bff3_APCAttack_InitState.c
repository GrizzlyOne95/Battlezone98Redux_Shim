/*
 * Entry: 0040bff3
 * Name: APCAttack::InitState
 * Namespace: APCAttack
 * Signature: void InitState(APCAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCAttack::InitState(APCAttack *this)

{
  int iVar1;
  GameObject *pGVar2;
  undefined4 *puVar3;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar2;
    if ((pGVar2 != (GameObject *)0x0) && (*(int *)(*(int *)&this->field_0x14 + 0x2c0) != 0)) {
      *(undefined4 *)&this->field_0xc = 2;
      puVar3 = (undefined4 *)(**(code **)(pGVar2->_padding_ + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar3;
      *(undefined4 *)&this->field_0x30 = puVar3[1];
      *(undefined4 *)&this->field_0x34 = puVar3[2];
      goto LAB_0040c063;
    }
    *(undefined4 *)&this->field_0xc = 0xd;
  }
  else {
    if (iVar1 == 2) {
LAB_0040c063:
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
  }
  return;
}
