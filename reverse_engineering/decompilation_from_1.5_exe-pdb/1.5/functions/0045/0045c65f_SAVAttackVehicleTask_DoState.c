/*
 * Entry: 0045c65f
 * Name: SAVAttackVehicleTask::DoState
 * Namespace: SAVAttackVehicleTask
 * Signature: void DoState(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackVehicleTask::DoState(SAVAttackVehicleTask *this)

{
  int iVar1;
  int iVar2;
  float fVar3;
  bool bVar4;
  char cVar5;
  bool bVar6;
  GameObject *pGVar7;
  VECTOR_3D *pVVar8;
  AttackerInfo *pAVar9;
  float *pfVar10;
  float *pfVar11;
  float fVar12;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar7 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar7;
  if (((pGVar7 == (GameObject *)0x0) ||
      (bVar4 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar7), bVar4)) ||
     (*(int *)(*(int *)&this->field_0x14 + 0x198) == 0)) {
    *(undefined4 *)&this->field_0x10 = 0xd;
    return;
  }
  pVVar8 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  pGVar7 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar8);
  *(GameObject **)&this->field_0x80 = pGVar7;
  if (pGVar7 == *(GameObject **)&this->field_0x1c) {
    *(undefined4 *)&this->field_0x80 = 0;
  }
  bVar4 = IsInTransition(*(Craft **)&this->field_0x14);
  if ((!bVar4) && (this->field_0x20 != '\0')) {
    UnitTask::CleanStuck((UnitTask *)this);
  }
  cVar5 = (**(code **)(**(int **)&this->field_0x14 + 0x68))();
  if (cVar5 == '\0') {
    bVar6 = AbleToHitFromGround(this);
  }
  else {
    bVar6 = UnitTask::AbleToHit((UnitTask *)this);
  }
  this->field_0xc8 = bVar6;
  iVar2 = *(int *)&this->field_0xc;
  if (iVar2 == 2) {
LAB_0045c735:
    cVar5 = (**(code **)(**(int **)&this->field_0x14 + 100))();
    if (cVar5 == '\0') {
LAB_0045c78b:
      DoSit(this);
      goto LAB_0045c99e;
    }
    if (((*(int *)&this->field_0xc == 2) && (this->field_0xc8 != '\0')) &&
       (*(float *)&this->field_0xd8 < *(float *)&this->field_0xa4 * 0.75)) {
      *(undefined4 *)&this->field_0x10 = 5;
      goto LAB_0045c99e;
    }
    pfVar11 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    fVar12 = *pfVar11 - *(float *)&this->field_0x2c;
    fVar3 = pfVar11[2] - *(float *)&this->field_0x34;
    if (10000.0 < fVar3 * fVar3 + fVar12 * fVar12) goto LAB_0045c853;
    pfVar11 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    fVar12 = *pfVar11 - *(float *)&this->field_0x38;
    fVar3 = pfVar11[2] - *(float *)&this->field_0x40;
    if (400.0 <= fVar3 * fVar3 + fVar12 * fVar12) {
      UnitTask::DoGoto((UnitTask *)this);
      goto LAB_0045c99e;
    }
  }
  else {
    if (iVar2 != 5) {
      if (iVar2 != 0xe) {
        if (iVar2 != 0xf) goto LAB_0045c99e;
        goto LAB_0045c735;
      }
      cVar5 = (**(code **)(**(int **)&this->field_0x14 + 100))();
      if (cVar5 != '\0') {
        if (this->field_0x20 != '\0') {
          fVar12 = Get_Time();
          *(float *)&this->field_0x124 = fVar12 + 5.0;
        }
        fVar12 = Get_Time();
        if (*(float *)&this->field_0x124 < fVar12) goto LAB_0045c853;
      }
      goto LAB_0045c78b;
    }
    cVar5 = (**(code **)(**(int **)&this->field_0x14 + 100))();
    if (cVar5 != '\0') {
      pAVar9 = AttackGroup::GetLeft
                         (*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
      if (pAVar9 != (AttackerInfo *)0x0) {
        UnitTask::DoBlast((UnitTask *)this);
        pfVar11 = (float *)(**(code **)(pAVar9->attacker->_padding_ + 0xc))();
        pfVar10 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
        if ((pfVar10[2] - pfVar11[2]) * (pfVar10[2] - pfVar11[2]) +
            (*pfVar10 - *pfVar11) * (*pfVar10 - *pfVar11) < 1600.0) {
          *(undefined4 *)(iVar1 + 0xcc) = 0x3f800000;
          goto LAB_0045c99e;
        }
      }
      (**(code **)(**(int **)&this->field_0x14 + 0x60))();
      goto LAB_0045c99e;
    }
    if (*(float *)&this->field_0xa4 * 1.1 < *(float *)&this->field_0xd8) {
LAB_0045c853:
      *(undefined4 *)&this->field_0x10 = 0xf;
      goto LAB_0045c99e;
    }
    cVar5 = (**(code **)(**(int **)&this->field_0x14 + 0x68))();
    if (cVar5 == '\0') {
      DoSit(this);
      fVar12 = Get_Time();
      *(float *)&this->field_0x124 = fVar12 + 15.0;
      fVar12 = Get_Time();
      *(float *)&this->field_0x10c = fVar12 + 3.0;
      goto LAB_0045c99e;
    }
    fVar12 = Get_Time();
    if (*(float *)&this->field_0x124 < fVar12) {
      *(undefined4 *)&this->field_0x10 = 0xe;
      goto LAB_0045c99e;
    }
    UnitTask::DoStand((UnitTask *)this);
    bVar6 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,1.0);
    if (bVar6) {
      *(undefined4 *)(iVar1 + 0xcc) = 0x3e800000;
    }
    if ((this->field_0xc8 == '\0') || (bVar6)) {
      UnitTask::UpdateWeapon((UnitTask *)this,false);
    }
    else {
      UnitTask::UpdateWeapon((UnitTask *)this,true);
      fVar12 = Get_Time();
      *(float *)&this->field_0x10c = fVar12 + 3.0;
    }
    fVar12 = Get_Time();
    if (fVar12 <= *(float *)&this->field_0x10c) goto LAB_0045c99e;
  }
  *(undefined4 *)&this->field_0x10 = 2;
LAB_0045c99e:
  this->field_0x20 = bVar4;
  return;
}
