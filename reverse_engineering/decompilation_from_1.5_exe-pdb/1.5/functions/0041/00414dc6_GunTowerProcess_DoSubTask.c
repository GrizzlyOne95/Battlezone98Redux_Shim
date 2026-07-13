/*
 * Entry: 00414dc6
 * Name: GunTowerProcess::DoSubTask
 * Namespace: GunTowerProcess
 * Signature: bool DoSubTask(GunTowerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GunTowerProcess::DoSubTask(GunTowerProcess *this)

{
  GameObject *pGVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  GunTowerProcess *local_8;
  
  iVar4 = *(int *)&this->field_0x18;
  if ((iVar4 == 3) && (iVar5 = *(int *)&this->field_0x20, iVar5 != 0)) {
LAB_00414de0:
    *(int *)&this->field_0x1c = iVar5;
LAB_00414de3:
    *(undefined4 *)&this->field_0x34 = *(undefined4 *)&this->field_0x24;
    *(undefined4 *)&this->field_0x20 = 0;
    return true;
  }
  bVar6 = *(int *)(*(int *)&this->field_0x2c + 0x280) != 0;
  if (iVar4 == 0x10) {
    if (bVar6) {
      *(undefined4 *)&this->field_0x1c = *(undefined4 *)&this->field_0x20;
      goto LAB_00414de3;
    }
  }
  else if (!bVar6) {
    iVar5 = *(int *)&this->field_0x20;
    if (iVar5 == 0) {
      *(int *)&this->field_0x20 = iVar4;
      *(undefined4 *)&this->field_0x24 = *(undefined4 *)&this->field_0x34;
      *(undefined4 *)&this->field_0x1c = 0x10;
      return true;
    }
    goto LAB_00414de0;
  }
  local_8 = this;
  if (iVar4 != 7) {
    if ((iVar4 != 0x10) && (fVar7 = Get_Time(), *(float *)&this->field_0x28 <= fVar7)) {
      local_8 = (GunTowerProcess *)0x471c4000;
      pGVar1 = GetClosestEnemyWithin(*(GameObject **)&this->field_0x2c,(float *)&local_8);
      if (pGVar1 != (GameObject *)0x0) {
        *(undefined4 *)&this->field_0x20 = *(undefined4 *)&this->field_0x18;
        *(undefined4 *)&this->field_0x24 = *(undefined4 *)&this->field_0x34;
        *(undefined4 *)&this->field_0x1c = 7;
        iVar4 = GameObject::GetHandle(pGVar1);
        goto LAB_00414ed8;
      }
      Rand_Counter = Rand_Counter + 1U & 0xff;
      fVar7 = Pseudo_Rand_Number[Rand_Counter];
      fVar8 = Get_Time();
      *(float *)&this->field_0x28 = fVar7 * 3.0 + fVar8 + 7.0;
    }
    return false;
  }
  if (*(int *)&this->field_0x20 == 0) {
    *(undefined4 *)&this->field_0x20 = 3;
  }
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  if (pGVar1 != (GameObject *)0x0) {
    pfVar2 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
    pfVar3 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x2c + 0x20) + 0xc))();
    if ((pfVar3[2] - pfVar2[2]) * (pfVar3[2] - pfVar2[2]) +
        (*pfVar3 - *pfVar2) * (*pfVar3 - *pfVar2) <= 40000.0) {
      return false;
    }
  }
  *(undefined4 *)&this->field_0x1c = *(undefined4 *)&this->field_0x20;
  iVar4 = *(int *)&this->field_0x24;
  *(undefined4 *)&this->field_0x20 = 0;
LAB_00414ed8:
  *(int *)&this->field_0x34 = iVar4;
  return true;
}
