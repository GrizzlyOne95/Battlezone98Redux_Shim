/*
 * Entry: 00412fec
 * Name: GechAttack::DoState
 * Namespace: GechAttack
 * Signature: void DoState(GechAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechAttack::DoState(GechAttack *this)

{
  int iVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  undefined4 *puVar7;
  float *pfVar8;
  undefined4 uVar9;
  
  uVar9 = 0xd;
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar5;
  if (((pGVar5 == (GameObject *)0x0) ||
      (bVar4 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar5), bVar4)) ||
     (*(int *)(*(int *)&this->field_0x14 + 0x198) == 0)) {
LAB_004131ae:
    *(undefined4 *)&this->field_0x10 = uVar9;
  }
  else {
    pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    pGVar5 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar6);
    *(GameObject **)&this->field_0x80 = pGVar5;
    uVar9 = 3;
    this->field_0xc8 = 0;
    if (3 < *(int *)(*(int *)&this->field_0x14 + 0x210)) {
      *(undefined4 *)&this->field_0xf8 = 0x3f800000;
      *(undefined4 *)&this->field_0xfc = 0x3f800000;
    }
    iVar1 = *(int *)&this->field_0xc;
    if (iVar1 == 2) {
      bVar4 = UnitTask::AbleToHit((UnitTask *)this);
      if (bVar4) {
        *(undefined4 *)&this->field_0x10 = 5;
        return;
      }
      bVar4 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar4) goto LAB_004131ae;
      pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      fVar2 = *pfVar8 - *(float *)&this->field_0x2c;
      fVar3 = pfVar8[2] - *(float *)&this->field_0x34;
      if ((fVar3 * fVar3 + fVar2 * fVar2 <= 10000.0) &&
         (pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))(),
         fVar2 = *pfVar8 - *(float *)&this->field_0x38,
         fVar3 = pfVar8[2] - *(float *)&this->field_0x40, 100.0 <= fVar3 * fVar3 + fVar2 * fVar2)) {
        UnitTask::DoGoto((UnitTask *)this);
        return;
      }
      puVar7 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    }
    else {
      if (iVar1 == 3) {
        UnitTask::DoStuck((UnitTask *)this);
        return;
      }
      if (iVar1 != 5) {
        return;
      }
      bVar4 = UnitTask::AbleToHit((UnitTask *)this);
      this->field_0xc8 = bVar4;
      if (bVar4) {
        UnitTask::DoBlast((UnitTask *)this);
        if ((this->field_0xc8 == '\0') ||
           (bVar4 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,
                                  1.0), bVar4)) {
          bVar4 = false;
        }
        else {
          bVar4 = true;
        }
        UnitTask::UpdateWeapon((UnitTask *)this,bVar4);
        return;
      }
      puVar7 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    }
    *(undefined4 *)&this->field_0x2c = *puVar7;
    *(undefined4 *)&this->field_0x30 = puVar7[1];
    *(undefined4 *)&this->field_0x34 = puVar7[2];
    *(undefined4 *)&this->field_0x10 = 2;
  }
  return;
}
