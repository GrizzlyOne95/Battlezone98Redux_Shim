/*
 * Entry: 0045c34d
 * Name: SAVAttackPersonTask::DoState
 * Namespace: SAVAttackPersonTask
 * Signature: void DoState(SAVAttackPersonTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackPersonTask::DoState(SAVAttackPersonTask *this)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  bool bVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  float *pfVar7;
  float *pfVar8;
  undefined4 *puVar9;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar5;
  if (pGVar5 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  pGVar5 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar6);
  *(GameObject **)&this->field_0x80 = pGVar5;
  bVar2 = IsInTransition(*(Craft **)&this->field_0x14);
  if ((!bVar2) && (this->field_0x20 != '\0')) {
    UnitTask::CleanStuck((UnitTask *)this);
  }
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 2) {
    pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if ((pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
        (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7) < 5625.0) {
      *(undefined4 *)&this->field_0x10 = 5;
      goto LAB_0045c4a9;
    }
    if (!bVar2) {
      bVar4 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar4) {
        *(undefined4 *)&this->field_0x10 = 3;
      }
      else {
        UnitTask::DoGoto((UnitTask *)this);
      }
      goto LAB_0045c4a9;
    }
  }
  else {
    if (iVar1 == 3) {
      UnitTask::DoStuck((UnitTask *)this);
      goto LAB_0045c4a9;
    }
    if (iVar1 != 5) goto LAB_0045c4a9;
    pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if (10000.0 < (pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
                  (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7)) {
      puVar9 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar9;
      *(undefined4 *)&this->field_0x30 = puVar9[1];
      *(undefined4 *)&this->field_0x34 = puVar9[2];
      *(undefined4 *)&this->field_0x10 = 2;
      goto LAB_0045c4a9;
    }
    cVar3 = (**(code **)(**(int **)&this->field_0x14 + 0x68))();
    if (cVar3 != '\0') {
      DoMulch(this);
      goto LAB_0045c4a9;
    }
  }
  UnitTask::DoSit((UnitTask *)this);
LAB_0045c4a9:
  this->field_0x20 = bVar2;
  return;
}
