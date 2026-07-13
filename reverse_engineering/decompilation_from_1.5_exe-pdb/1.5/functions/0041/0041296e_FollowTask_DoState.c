/*
 * Entry: 0041296e
 * Name: FollowTask::DoState
 * Namespace: FollowTask
 * Signature: void DoState(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowTask::DoState(FollowTask *this)

{
  int iVar1;
  Carrier *pCVar2;
  float fVar3;
  float fVar4;
  VECTOR_3D VVar5;
  bool bVar6;
  GameObject *pGVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 *puVar10;
  VECTOR_3D *pVVar11;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  undefined4 local_10;
  float local_c;
  char local_5;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar7 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar7;
  if (pGVar7 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pGVar7 = AvoidObject(*(GameObject **)&this->field_0x14,(GameObject *)0x0);
  *(GameObject **)&this->field_0x80 = pGVar7;
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    UnitTask::DoSit((UnitTask *)this);
    goto LAB_00412b2e;
  }
  if (iVar1 == 2) {
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar9 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if ((pfVar9[2] - pfVar8[2]) * (pfVar9[2] - pfVar8[2]) +
        (*pfVar9 - *pfVar8) * (*pfVar9 - *pfVar8) < 2500.0) {
      *(undefined4 *)&this->field_0x10 = 4;
      goto LAB_00412b2e;
    }
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    fVar3 = *pfVar8 - *(float *)&this->field_0x2c;
    fVar4 = pfVar8[2] - *(float *)&this->field_0x34;
    if (fVar4 * fVar4 + fVar3 * fVar3 <= 10000.0) {
      bVar6 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar6) goto LAB_00412a31;
      pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      fVar3 = *pfVar8 - *(float *)&this->field_0x38;
      fVar4 = pfVar8[2] - *(float *)&this->field_0x40;
      if (225.0 <= fVar4 * fVar4 + fVar3 * fVar3) {
        UnitTask::DoGoto((UnitTask *)this);
        goto LAB_00412b2e;
      }
    }
    *(undefined4 *)&this->field_0x10 = 2;
    puVar10 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    *(undefined4 *)&this->field_0x2c = *puVar10;
    *(undefined4 *)&this->field_0x30 = puVar10[1];
    *(undefined4 *)&this->field_0x34 = puVar10[2];
  }
  else {
    if (iVar1 == 3) {
      UnitTask::DoStuck((UnitTask *)this);
      goto LAB_00412b2e;
    }
    if (iVar1 != 4) goto LAB_00412b2e;
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pfVar9 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if (10000.0 < (pfVar9[2] - pfVar8[2]) * (pfVar9[2] - pfVar8[2]) +
                  (*pfVar9 - *pfVar8) * (*pfVar9 - *pfVar8)) {
      puVar10 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar10;
      *(undefined4 *)&this->field_0x30 = puVar10[1];
      *(undefined4 *)&this->field_0x34 = puVar10[2];
      *(undefined4 *)&this->field_0x10 = 2;
      goto LAB_00412b2e;
    }
    bVar6 = UnitTask::IsStuck((UnitTask *)this);
    if (!bVar6) {
      UnitTask::DoFollow((UnitTask *)this);
      goto LAB_00412b2e;
    }
LAB_00412a31:
    *(undefined4 *)&this->field_0x10 = 3;
  }
LAB_00412b2e:
  if (*(int *)&this->field_0xc != 4) {
    return;
  }
  pCVar2 = (*(GameObject **)&this->field_0x14)->carrier;
  if (pCVar2 == (Carrier *)0x0) {
    return;
  }
  if (pCVar2->enabled == 0) {
    return;
  }
  if (*(int *)(*(int *)(*(int *)&this->field_0xb8 + 8) + 0xc) != 0x44495350) {
    local_c = *(float *)&this->field_0xa4;
    pGVar7 = GetClosestEnemyWithin(*(GameObject **)&this->field_0x14,&local_c);
    if (pGVar7 != (GameObject *)0x0) {
      local_10 = *(undefined4 *)&this->field_0x1c;
      *(GameObject **)&this->field_0x1c = pGVar7;
      local_5 = UnitTask::AbleToHit((UnitTask *)this);
      VVar5.x = *(float *)&this->field_0xe8;
      VVar5.y = *(float *)&this->field_0xec;
      VVar5.z = *(float *)&this->field_0xf0;
      pVVar11 = ScaleVector(&local_28,*(float *)&this->field_0x9c * 0.5 - 0.5,VVar5);
      local_1c.x = pVVar11->x;
      local_1c.y = pVVar11->y;
      local_1c.z = pVVar11->z;
      UnitTask::LookAtLocalPos((UnitTask *)this,(VECTOR_3D *)&this->field_0xcc,&local_1c);
      if ((local_5 == '\0') ||
         (bVar6 = MayHitFriends(*(GameObject **)&this->field_0x14,local_c,0.3,1.0), bVar6)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      UnitTask::UpdateWeapon((UnitTask *)this,bVar6);
      *(undefined4 *)&this->field_0x1c = local_10;
      return;
    }
    return;
  }
  return;
}
