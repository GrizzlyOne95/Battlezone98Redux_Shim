/*
 * Entry: 0040c072
 * Name: APCAttack::DoState
 * Namespace: APCAttack
 * Signature: void DoState(APCAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCAttack::DoState(APCAttack *this)

{
  int iVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  float *pfVar7;
  float *pfVar8;
  undefined4 *puVar9;
  
  if (*(int *)&this->field_0xc != 0xd) {
    pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar5;
    if (pGVar5 == (GameObject *)0x0) {
      *(undefined4 *)&this->field_0x10 = 0xd;
    }
    else {
      pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      pGVar5 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar6);
      *(GameObject **)&this->field_0x80 = pGVar5;
      iVar1 = *(int *)&this->field_0xc;
      if (iVar1 == 2) {
        if (0 < *(int *)(*(int *)&this->field_0x14 + 0x2c0)) {
          pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
          pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
          if ((pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
              (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7) < 5625.0) {
            (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
            *(undefined4 *)&this->field_0x10 = 5;
            return;
          }
          bVar4 = UnitTask::IsStuck((UnitTask *)this);
          if (bVar4) {
            *(undefined4 *)&this->field_0x10 = 3;
            return;
          }
          pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
          fVar2 = *pfVar7 - *(float *)&this->field_0x2c;
          fVar3 = pfVar7[2] - *(float *)&this->field_0x34;
          if ((fVar3 * fVar3 + fVar2 * fVar2 <= 10000.0) &&
             (pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))(),
             fVar2 = *pfVar7 - *(float *)&this->field_0x38,
             fVar3 = pfVar7[2] - *(float *)&this->field_0x40, 100.0 <= fVar3 * fVar3 + fVar2 * fVar2
             )) {
            UnitTask::DoGoto((UnitTask *)this);
            return;
          }
          puVar9 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
          *(undefined4 *)&this->field_0x2c = *puVar9;
          *(undefined4 *)&this->field_0x30 = puVar9[1];
          *(undefined4 *)&this->field_0x34 = puVar9[2];
          *(undefined4 *)&this->field_0x10 = 2;
          return;
        }
      }
      else {
        if (iVar1 == 3) {
          UnitTask::DoStuck((UnitTask *)this);
          return;
        }
        if (iVar1 != 5) {
          return;
        }
        if (0 < *(int *)(*(int *)&this->field_0x14 + 0x2c0)) {
          iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
          *(undefined4 *)(iVar1 + 0xd0) = 0;
          *(undefined4 *)(iVar1 + 0xc4) = 0;
          *(undefined4 *)(iVar1 + 0xd4) = 0;
          *(undefined4 *)(iVar1 + 200) = 0;
          return;
        }
      }
      *(undefined4 *)&this->field_0x10 = 0xd;
    }
  }
  return;
}
