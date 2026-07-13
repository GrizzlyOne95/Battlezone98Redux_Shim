/*
 * Entry: 00458250
 * Name: PersonAttack::InitState
 * Namespace: PersonAttack
 * Signature: void InitState(PersonAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonAttack::InitState(PersonAttack *this)

{
  int iVar1;
  AttackerInfo *pAVar2;
  float *pfVar3;
  float *pfVar4;
  GameObject *pGVar5;
  undefined4 *puVar6;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0x10 = 4;
  }
  else if (iVar1 == 2) {
    pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    if (pGVar5 != (GameObject *)0x0) {
      puVar6 = (undefined4 *)(**(code **)(pGVar5->_padding_ + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar6;
      *(undefined4 *)&this->field_0x30 = puVar6[1];
      *(undefined4 *)&this->field_0x34 = puVar6[2];
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  else {
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
    if (iVar1 == 4) {
      pAVar2 = AttackGroup::GetLeft
                         (*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
      if (pAVar2 != (AttackerInfo *)0x0) {
        pfVar3 = (float *)(**(code **)(pAVar2->attacker->_padding_ + 0xc))();
        pfVar4 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
        if ((pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
            (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3) <= 900.0) {
          *(undefined4 *)&this->field_0x114 = 0;
          *(undefined4 *)&this->field_0x118 = 0xc1200000;
          return;
        }
      }
      *(undefined4 *)&this->field_0x10 = 2;
    }
  }
  return;
}
