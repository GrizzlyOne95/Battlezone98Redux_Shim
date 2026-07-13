/*
 * Entry: 004634fa
 * Name: SoldierAttack::DoState
 * Namespace: SoldierAttack
 * Signature: void DoState(SoldierAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierAttack::DoState(SoldierAttack *this)

{
  int iVar1;
  float fVar2;
  bool bVar3;
  GameObject *pGVar4;
  VECTOR_3D *pVVar5;
  AttackerInfo *pAVar6;
  float *pfVar7;
  float *pfVar8;
  undefined4 uVar9;
  float fVar10;
  
  uVar9 = 0xd;
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar4 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar4;
  if (((pGVar4 == (GameObject *)0x0) ||
      (bVar3 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar4), bVar3)) ||
     (*(int *)(*(int *)&this->field_0x14 + 0x198) == 0)) {
LAB_0046371b:
    *(undefined4 *)&this->field_0x10 = uVar9;
    return;
  }
  pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  pGVar4 = NearestVehicle(*(GameObject **)&this->field_0x14,pVVar5);
  *(GameObject **)&this->field_0x80 = pGVar4;
  iVar1 = *(int *)&this->field_0xc;
  uVar9 = 2;
  this->field_0xc8 = 0;
  if (iVar1 == 2) {
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    if (bVar3) {
      *(undefined4 *)&this->field_0x10 = 5;
      return;
    }
    bVar3 = UnitTask::IsStuck((UnitTask *)this);
    if (bVar3) {
      *(undefined4 *)&this->field_0x10 = 3;
      return;
    }
    pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    fVar10 = *pfVar7 - *(float *)&this->field_0x2c;
    fVar2 = pfVar7[2] - *(float *)&this->field_0x34;
    if ((fVar2 * fVar2 + fVar10 * fVar10 <= 10000.0) &&
       (pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))(),
       fVar10 = *pfVar7 - *(float *)&this->field_0x38,
       fVar2 = pfVar7[2] - *(float *)&this->field_0x40, 100.0 <= fVar2 * fVar2 + fVar10 * fVar10)) {
      UnitTask::DoGoto((UnitTask *)this);
      return;
    }
    goto LAB_0046371b;
  }
  if (iVar1 == 3) {
    UnitTask::DoStuck((UnitTask *)this);
    return;
  }
  if (iVar1 == 4) {
    pAVar6 = AttackGroup::GetLeft
                       (*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
    if ((pAVar6 != (AttackerInfo *)0x0) && (pAVar6->attackTask->curState == 2)) {
      *(GameObject **)&this->field_0x1c = pAVar6->attacker;
      UnitTask::DoFollow((UnitTask *)this);
      return;
    }
    goto LAB_0046371b;
  }
  if (iVar1 != 5) {
    return;
  }
  bVar3 = UnitTask::AbleToHit((UnitTask *)this);
  if (!bVar3) goto LAB_0046371b;
  UnitTask::DoBlast((UnitTask *)this);
  iVar1 = (*(GameObject **)&this->field_0x14)[1]._padding_;
  bVar3 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,1.0);
  pAVar6 = AttackGroup::GetLeft
                     (*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
  if (pAVar6 == (AttackerInfo *)0x0) {
LAB_0046361e:
    if (!bVar3) goto LAB_00463642;
    fVar10 = Min(*(float *)(iVar1 + 0xcc) + 0.25,1.0);
  }
  else {
    pfVar7 = (float *)(**(code **)(pAVar6->attacker->_padding_ + 0xc))();
    pfVar8 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    if (25.0 <= (pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
                (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7)) goto LAB_0046361e;
    fVar10 = 1.0;
  }
  *(float *)(iVar1 + 0xcc) = fVar10;
LAB_00463642:
  UnitTask::UpdateWeapon((UnitTask *)this,!bVar3);
  return;
}
