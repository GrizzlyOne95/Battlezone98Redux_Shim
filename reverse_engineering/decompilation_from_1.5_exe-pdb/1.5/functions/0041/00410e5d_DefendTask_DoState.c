/*
 * Entry: 00410e5d
 * Name: DefendTask::DoState
 * Namespace: DefendTask
 * Signature: void DoState(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DefendTask::DoState(DefendTask *this)

{
  float fVar1;
  int iVar2;
  float fVar3;
  bool bVar4;
  GameObject *pGVar5;
  float *pfVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float fVar9;
  
  pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar5;
  if (pGVar5 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    *(undefined4 *)&this->field_0x18 = 0;
    return;
  }
  fVar9 = (*(GameObject **)&this->field_0x14)->collisionRadius;
  fVar1 = pGVar5->collisionRadius;
  *(undefined4 *)&this->field_0x84 = 0;
  fVar9 = fVar9 + fVar1 + 20.0;
  pGVar5 = AvoidObject(*(GameObject **)&this->field_0x14,(GameObject *)0x0);
  *(GameObject **)&this->field_0x80 = pGVar5;
  iVar2 = *(int *)&this->field_0xc;
  if (iVar2 == 2) {
    pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    fVar1 = *pfVar6 - *(float *)&this->field_0x2c;
    fVar3 = pfVar6[2] - *(float *)&this->field_0x34;
    if ((fVar9 - 10.0) * (fVar9 - 10.0) <= fVar3 * fVar3 + fVar1 * fVar1) {
      bVar4 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar4) {
        *(undefined4 *)&this->field_0x10 = 3;
        return;
      }
      UnitTask::DoGoto((UnitTask *)this);
      return;
    }
  }
  else {
    if (iVar2 == 3) {
      UnitTask::DoStuck((UnitTask *)this);
      return;
    }
    if (iVar2 != 6) {
      return;
    }
    DoWander(this);
    pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if (fVar9 * fVar9 <
        (pfVar7[2] - pfVar6[2]) * (pfVar7[2] - pfVar6[2]) +
        (*pfVar7 - *pfVar6) * (*pfVar7 - *pfVar6)) {
      puVar8 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar8;
      *(undefined4 *)&this->field_0x30 = puVar8[1];
      *(undefined4 *)&this->field_0x34 = puVar8[2];
      *(undefined4 *)&this->field_0x10 = 2;
      return;
    }
    fVar9 = Get_Time();
    if (fVar9 <= *(float *)&this->field_0x124) {
      return;
    }
  }
  *(undefined4 *)&this->field_0x10 = 6;
  return;
}
