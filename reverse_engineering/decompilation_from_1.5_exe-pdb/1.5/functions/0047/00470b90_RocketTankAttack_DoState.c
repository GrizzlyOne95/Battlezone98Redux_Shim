/*
 * Entry: 00470b90
 * Name: RocketTankAttack::DoState
 * Namespace: RocketTankAttack
 * Signature: void DoState(RocketTankAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankAttack::DoState(RocketTankAttack *this)

{
  int iVar1;
  float fVar2;
  bool bVar3;
  GameObject *pGVar4;
  VECTOR_3D *pVVar5;
  float *pfVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float fVar9;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar4 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar4;
  if (((pGVar4 == (GameObject *)0x0) ||
      (bVar3 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar4), bVar3)) ||
     (*(int *)(*(int *)&this->field_0x14 + 0x198) == 0)) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  pGVar4 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar5);
  *(GameObject **)&this->field_0x80 = pGVar4;
  iVar1 = *(int *)&this->field_0xc;
  this->field_0xc8 = 0;
  if (iVar1 == 2) {
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    if (bVar3) {
      *(undefined4 *)&this->field_0x10 = 5;
    }
    else {
      bVar3 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar3) {
LAB_00470c84:
        *(undefined4 *)&this->field_0x10 = 3;
      }
      else {
        pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
        fVar9 = *pfVar6 - *(float *)&this->field_0x2c;
        fVar2 = pfVar6[2] - *(float *)&this->field_0x34;
        if (fVar2 * fVar2 + fVar9 * fVar9 <= 10000.0) {
          pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
          fVar9 = *pfVar6 - *(float *)&this->field_0x38;
          fVar2 = pfVar6[2] - *(float *)&this->field_0x40;
          if (100.0 <= fVar2 * fVar2 + fVar9 * fVar9) {
            UnitTask::DoGoto((UnitTask *)this);
            goto LAB_00470daa;
          }
        }
        else {
          puVar8 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
LAB_00470c6c:
          *(undefined4 *)&this->field_0x2c = *puVar8;
          *(undefined4 *)&this->field_0x30 = puVar8[1];
          *(undefined4 *)&this->field_0x34 = puVar8[2];
        }
        *(undefined4 *)&this->field_0x10 = 2;
      }
    }
  }
  else if (iVar1 == 3) {
    UnitTask::DoStuck((UnitTask *)this);
  }
  else if (iVar1 == 5) {
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    this->field_0xc8 = bVar3;
    if (!bVar3) {
      pfVar6 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      if (10000.0 < (pfVar7[2] - pfVar6[2]) * (pfVar7[2] - pfVar6[2]) +
                    (*pfVar7 - *pfVar6) * (*pfVar7 - *pfVar6)) {
        puVar8 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
        goto LAB_00470c6c;
      }
    }
    bVar3 = UnitTask::IsStuck((UnitTask *)this);
    if (bVar3) goto LAB_00470c84;
    UnitTask::DoBlast((UnitTask *)this);
    pfVar6 = (float *)(*(int *)(*(int *)&this->field_0x14 + 0x228) + 0xd0);
    if (*pfVar6 < 0.0) {
      *pfVar6 = -0.3;
    }
    bVar3 = false;
    if (this->field_0xc8 != '\0') goto LAB_00470db1;
    fVar9 = TimeStep();
    fVar9 = *(float *)&this->field_0xf4 - fVar9 * 5.0;
    *(float *)&this->field_0xf4 = fVar9;
    if (fVar9 < 20.0) {
      *(undefined4 *)&this->field_0xf4 = 0x41a00000;
    }
  }
LAB_00470daa:
  bVar3 = this->field_0xc8 == '\0';
LAB_00470db1:
  if ((bVar3) ||
     (bVar3 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,1.0),
     bVar3)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  UnitTask::UpdateWeapon((UnitTask *)this,bVar3);
  UnitTask::UpdateSpecial((UnitTask *)this);
  return;
}
