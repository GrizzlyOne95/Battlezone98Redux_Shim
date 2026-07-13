/*
 * Entry: 0045b6e8
 * Name: RescueTask::DoState
 * Namespace: RescueTask
 * Signature: void DoState(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::DoState(RescueTask *this)

{
  int iVar1;
  float fVar2;
  bool bVar3;
  GameObject *pGVar4;
  float *pfVar5;
  float *pfVar6;
  undefined4 *puVar7;
  float fVar8;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar4 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar4;
  if (pGVar4 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pGVar4 = AvoidObject(*(GameObject **)&this->field_0x14,pGVar4);
  *(GameObject **)&this->field_0x80 = pGVar4;
  pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
  pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
LAB_0045b793:
    UnitTask::DoSit((UnitTask *)this);
    return;
  }
  if (iVar1 == 2) {
    pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if ((pfVar6[2] - pfVar5[2]) * (pfVar6[2] - pfVar5[2]) +
        (*pfVar6 - *pfVar5) * (*pfVar6 - *pfVar5) < 2500.0) {
      *(undefined4 *)&this->field_0x10 = 4;
      return;
    }
    pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    fVar8 = *pfVar5 - *(float *)&this->field_0x2c;
    fVar2 = pfVar5[2] - *(float *)&this->field_0x34;
    if (fVar2 * fVar2 + fVar8 * fVar8 <= 10000.0) {
      bVar3 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar3) goto LAB_0045b8d0;
      pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      fVar8 = *pfVar5 - *(float *)&this->field_0x38;
      fVar2 = pfVar5[2] - *(float *)&this->field_0x40;
      if (225.0 <= fVar2 * fVar2 + fVar8 * fVar8) {
        UnitTask::DoGoto((UnitTask *)this);
        return;
      }
    }
    *(undefined4 *)&this->field_0x10 = 2;
    puVar7 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    *(undefined4 *)&this->field_0x2c = *puVar7;
    *(undefined4 *)&this->field_0x30 = puVar7[1];
    *(undefined4 *)&this->field_0x34 = puVar7[2];
  }
  else {
    if (iVar1 == 3) {
      UnitTask::DoStuck((UnitTask *)this);
      return;
    }
    if (iVar1 != 4) {
      if (iVar1 != 6) {
        return;
      }
      fVar8 = Get_TimeLocal();
      if (*(float *)&this->field_0x124 < fVar8) {
        *(undefined4 *)(*(int *)(*(int *)&this->field_0x14 + 0x228) + 0xe4) = 1;
        *(undefined4 *)&this->field_0x10 = 0xd;
        return;
      }
      goto LAB_0045b793;
    }
    if ((pfVar6[2] - pfVar5[2]) * (pfVar6[2] - pfVar5[2]) +
        (*pfVar6 - *pfVar5) * (*pfVar6 - *pfVar5) < 900.0) {
      fVar8 = Get_TimeLocal();
      *(undefined4 *)&this->field_0x10 = 6;
      *(float *)&this->field_0x124 = fVar8 + 1.0;
      return;
    }
    pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if (10000.0 < (pfVar6[2] - pfVar5[2]) * (pfVar6[2] - pfVar5[2]) +
                  (*pfVar6 - *pfVar5) * (*pfVar6 - *pfVar5)) {
      puVar7 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar7;
      *(undefined4 *)&this->field_0x30 = puVar7[1];
      *(undefined4 *)&this->field_0x34 = puVar7[2];
      *(undefined4 *)&this->field_0x10 = 2;
      return;
    }
    bVar3 = UnitTask::IsStuck((UnitTask *)this);
    if (!bVar3) {
      UnitTask::DoFollow((UnitTask *)this);
      return;
    }
LAB_0045b8d0:
    *(undefined4 *)&this->field_0x10 = 3;
  }
  return;
}
