/*
 * Entry: 00470892
 * Name: WingmanBlastAttack::DoState
 * Namespace: WingmanBlastAttack
 * Signature: void DoState(WingmanBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanBlastAttack::DoState(WingmanBlastAttack *this)

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
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar5 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar5;
  if (((pGVar5 == (GameObject *)0x0) ||
      (bVar4 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar5), bVar4)) ||
     (*(int *)(*(int *)&this->field_0x14 + 0x198) == 0)) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  pGVar5 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar6);
  *(GameObject **)&this->field_0x80 = pGVar5;
  iVar1 = *(int *)&this->field_0xc;
  this->field_0xc8 = 0;
  if (iVar1 == 2) {
    bVar4 = UnitTask::AbleToHit((UnitTask *)this);
    this->field_0xc8 = bVar4;
    if (bVar4) {
      *(undefined4 *)&this->field_0x10 = 5;
      goto LAB_00470a37;
    }
    bVar4 = UnitTask::IsStuck((UnitTask *)this);
    if (bVar4) {
      *(undefined4 *)&this->field_0x10 = 3;
      goto LAB_00470a37;
    }
    pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    fVar2 = *pfVar7 - *(float *)&this->field_0x2c;
    fVar3 = pfVar7[2] - *(float *)&this->field_0x34;
    if (fVar3 * fVar3 + fVar2 * fVar2 <= 10000.0) {
      pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      fVar2 = *pfVar7 - *(float *)&this->field_0x38;
      fVar3 = pfVar7[2] - *(float *)&this->field_0x40;
      if (100.0 <= fVar3 * fVar3 + fVar2 * fVar2) {
        UnitTask::DoGoto((UnitTask *)this);
        goto LAB_00470a37;
      }
    }
    else {
      puVar9 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
LAB_0047096a:
      *(undefined4 *)&this->field_0x2c = *puVar9;
      *(undefined4 *)&this->field_0x30 = puVar9[1];
      *(undefined4 *)&this->field_0x34 = puVar9[2];
    }
    *(undefined4 *)&this->field_0x10 = 2;
  }
  else {
    if (iVar1 == 3) {
      UnitTask::DoStuck((UnitTask *)this);
      goto LAB_00470a37;
    }
    if (iVar1 != 5) goto LAB_00470a37;
    bVar4 = UnitTask::AbleToHit((UnitTask *)this);
    this->field_0xc8 = bVar4;
    if (!bVar4) {
      pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      if (10000.0 < (pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
                    (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7)) {
        puVar9 = (undefined4 *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
        goto LAB_0047096a;
      }
    }
    UnitTask::DoBlast((UnitTask *)this);
  }
LAB_00470a37:
  if ((this->field_0xc8 == '\0') ||
     (bVar4 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,1.0),
     bVar4)) {
    bVar4 = false;
  }
  else {
    bVar4 = true;
  }
  UnitTask::UpdateWeapon((UnitTask *)this,bVar4);
  UnitTask::UpdateSpecial((UnitTask *)this);
  return;
}
