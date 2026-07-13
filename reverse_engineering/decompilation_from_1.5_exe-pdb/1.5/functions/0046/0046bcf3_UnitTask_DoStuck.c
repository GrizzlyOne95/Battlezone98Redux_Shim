/*
 * Entry: 0046bcf3
 * Name: UnitTask::DoStuck
 * Namespace: UnitTask
 * Signature: void DoStuck(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoStuck(UnitTask *this)

{
  VEHICLE *pVVar1;
  int iVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D_LONG VVar4;
  int *piVar5;
  bool bVar6;
  char cVar7;
  VECTOR_3D *pVVar8;
  int iVar9;
  Craft *pCVar10;
  _OBJ76 *p_Var11;
  VECTOR_3D *pVVar12;
  UnitTask *pUVar13;
  VHCL_CONTROL *pVVar14;
  float *pfVar15;
  float fVar16;
  Range_Search_Results local_15c;
  VECTOR_3D local_130;
  VECTOR_3D local_124;
  VECTOR_3D local_118;
  VECTOR_3D local_10c;
  VECTOR_3D local_100;
  VECTOR_3D local_f4;
  VECTOR_3D local_e8;
  float local_dc;
  float fStack_d8;
  float fStack_d4;
  float local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  float local_c4;
  float fStack_c0;
  float fStack_bc;
  float local_b8;
  float fStack_b4;
  float fStack_b0;
  float local_ac;
  float fStack_a8;
  float fStack_a4;
  float local_a0;
  float fStack_9c;
  float fStack_98;
  float local_94;
  float fStack_90;
  float fStack_8c;
  float local_88 [8];
  float local_68;
  VECTOR_3D local_64;
  VECTOR_3D_LONG local_58;
  VECTOR_3D local_40;
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  int *local_1c;
  VECTOR_3D local_18;
  UnitTask *local_c;
  char local_5;
  
  iVar9 = this->me->_padding_;
  local_58.x = *(double *)*(undefined1 (*) [12])(iVar9 + 0x48);
  pVVar12 = (VECTOR_3D *)(iVar9 + 0x20);
  local_58.y = *(double *)(iVar9 + 0x50);
  pVVar1 = this->me->vhcl;
  local_58.z = *(double *)(iVar9 + 0x58);
  pVVar14 = &pVVar1->control;
  VVar4.y._4_4_ = (int)((ulonglong)local_58.y >> 0x20);
  VVar4._0_12_ = *(undefined1 (*) [12])(iVar9 + 0x48);
  VVar4.z._0_4_ = SUB84(local_58.z,0);
  VVar4.z._4_4_ = (int)((ulonglong)local_58.z >> 0x20);
  local_c = this;
  Floor_GetFloor(VVar4,&local_68,&local_40);
  fVar16 = Clamp((*(float *)(iVar9 + 0x40) * local_40.z +
                 *(float *)(iVar9 + 0x3c) * local_40.y + local_40.x * *(float *)(iVar9 + 0x38)) *
                 -1.0,-1.0,1.0);
  (pVVar1->control).pitch = fVar16;
  local_5 = 0.7 < local_40.y;
  pVVar8 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  iVar2 = local_c->stuckState;
  if (iVar2 == 0) {
    (pVVar1->control).turbo = 0;
    (pVVar1->control).braccel = -0.1;
    pVVar14->steer = 0.0;
    bVar6 = OnBlocked(pVVar8);
    if (!bVar6) {
      fVar16 = Get_Time();
      local_c->stuckState = 10;
      local_c->nextStuck = fVar16 + 2.0;
      return;
    }
    fVar16 = Get_Time();
    local_34 = 8;
    local_c->nextStuck = fVar16 + 2.0;
    local_30 = 50.0;
    Range::Search(GameObject::objectRange,(double)(pVVar8->x - 50.0),(double)(pVVar8->z - 50.0),
                  (double)(pVVar8->x + 50.0),(double)(pVVar8->z + 50.0),&local_15c);
    local_e8.x = *(float *)(iVar9 + 0x38);
    local_e8.y = *(float *)(iVar9 + 0x3c);
    local_e8.z = *(float *)(iVar9 + 0x40);
    local_28 = pVVar12->x;
    local_24 = *(float *)(iVar9 + 0x24);
    local_20 = *(float *)(iVar9 + 0x28);
    local_18.x = ((VECTOR_3D *)(iVar9 + 0x38))->x;
    local_18.y = *(float *)(iVar9 + 0x3c);
    local_18.z = *(float *)(iVar9 + 0x40);
    pVVar8 = CombineVectors(&local_130,0.707107,*(VECTOR_3D *)(iVar9 + 0x38),0.707107,*pVVar12);
    local_d0 = pVVar12->x;
    local_dc = pVVar8->x;
    uStack_cc = *(undefined4 *)(iVar9 + 0x24);
    uStack_c8 = *(undefined4 *)(iVar9 + 0x28);
    fStack_d8 = pVVar8->y;
    fStack_d4 = pVVar8->z;
    local_18.x = pVVar12->x;
    local_18.y = *(float *)(iVar9 + 0x24);
    local_18.z = *(float *)(iVar9 + 0x28);
    local_28 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
    local_24 = *(float *)(iVar9 + 0x3c);
    local_20 = *(float *)(iVar9 + 0x40);
    pVVar8 = CombineVectors(&local_100,-0.707107,*(VECTOR_3D *)(iVar9 + 0x38),0.707107,*pVVar12);
    local_18.x = ((VECTOR_3D *)(iVar9 + 0x38))->x;
    local_c4 = pVVar8->x;
    local_18.y = *(float *)(iVar9 + 0x3c);
    local_18.z = *(float *)(iVar9 + 0x40);
    fStack_c0 = pVVar8->y;
    fStack_bc = pVVar8->z;
    pVVar8 = ScaleVector(&local_10c,-1.0,*(VECTOR_3D *)(iVar9 + 0x38));
    local_18.x = pVVar12->x;
    local_b8 = pVVar8->x;
    local_18.y = *(float *)(iVar9 + 0x24);
    local_18.z = *(float *)(iVar9 + 0x28);
    fStack_b4 = pVVar8->y;
    local_28 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
    local_24 = *(float *)(iVar9 + 0x3c);
    fStack_b0 = pVVar8->z;
    local_20 = *(float *)(iVar9 + 0x40);
    pVVar8 = CombineVectors(&local_124,-0.707107,*(VECTOR_3D *)(iVar9 + 0x38),-0.707107,*pVVar12);
    local_18.x = pVVar12->x;
    local_ac = pVVar8->x;
    local_18.y = *(float *)(iVar9 + 0x24);
    local_18.z = *(float *)(iVar9 + 0x28);
    fStack_a8 = pVVar8->y;
    fStack_a4 = pVVar8->z;
    pVVar8 = ScaleVector(&local_f4,-1.0,*pVVar12);
    local_18.x = pVVar12->x;
    local_a0 = pVVar8->x;
    local_18.y = *(float *)(iVar9 + 0x24);
    local_18.z = *(float *)(iVar9 + 0x28);
    fStack_9c = pVVar8->y;
    local_28 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
    local_24 = *(float *)(iVar9 + 0x3c);
    fStack_98 = pVVar8->z;
    local_20 = *(float *)(iVar9 + 0x40);
    pVVar8 = CombineVectors(&local_118,0.707107,*(VECTOR_3D *)(iVar9 + 0x38),-0.707107,*pVVar12);
    local_94 = pVVar8->x;
    fStack_90 = pVVar8->y;
    local_1c = (int *)0x0;
    fStack_8c = pVVar8->z;
    pVVar8 = &local_e8;
    do {
      local_2c = 50.0;
      VVar3.y._0_4_ = SUB84(local_58.y,0);
      VVar3.x = local_58.x;
      VVar3.y._4_4_ = (int)((ulonglong)local_58.y >> 0x20);
      VVar3.z._0_4_ = SUB84(local_58.z,0);
      VVar3.z._4_4_ = (int)((ulonglong)local_58.z >> 0x20);
      iVar9 = Terrain_GetIntersection(VVar3,*pVVar8,&local_2c,&local_18);
      piVar5 = local_1c;
      if ((iVar9 == 0) || (0.7 <= local_18.y)) {
        fVar16 = 50.0;
      }
      else {
        fVar16 = local_2c - (float)local_c->me->_padding_;
      }
      local_1c = (int *)((int)local_1c + 1);
      local_88[(int)piVar5] = fVar16;
      pVVar8 = pVVar8 + 1;
    } while ((int)local_1c < 8);
    iVar9 = (**(code **)local_c->me->_padding_)();
    local_64.x = (float)local_58.x;
    local_64.y = (*(float *)(iVar9 + 0x124) + *(float *)(iVar9 + 0x118)) * 0.5 + (float)local_58.y;
    local_64.z = (float)local_58.z;
    local_20 = (*(float *)(iVar9 + 0x124) - *(float *)(iVar9 + 0x118)) * 0.5;
    while (bVar6 = Range_Search_Results::Get_Next_Object(&local_15c,&local_1c), bVar6) {
      pCVar10 = (Craft *)GameObject::GetObj(*local_1c);
      if ((pCVar10 != (Craft *)0x0) && (pCVar10 != local_c->me)) {
        p_Var11 = (_OBJ76 *)(**(code **)(pCVar10->_padding_ + 0x30))();
        iVar9 = dynamic_object(p_Var11);
        if ((iVar9 == 0) ||
           ((iVar9 = IsCraft(p_Var11), iVar9 != 0 &&
            (cVar7 = (**(code **)(pCVar10->_padding_ + 100))(), cVar7 != '\0')))) {
          pVVar8 = &local_e8;
          pfVar15 = local_88;
          local_2c = 1.12104e-44;
          do {
            IntersectGameObject(&local_64,pVVar8,pfVar15,&local_18,(GameObject *)pCVar10,local_20);
            pfVar15 = pfVar15 + 1;
            pVVar8 = pVVar8 + 1;
            local_2c = (float)((int)local_2c + -1);
          } while (local_2c != 0.0);
        }
      }
    }
    iVar9 = 0;
    pVVar8 = &local_e8;
    do {
      fVar16 = DistToOffBlocked(&local_58,pVVar8,local_88[iVar9]);
      if ((fVar16 < local_30) && (fVar16 < local_88[iVar9])) {
        local_30 = fVar16;
        local_34 = iVar9;
      }
      iVar9 = iVar9 + 1;
      pVVar8 = pVVar8 + 1;
    } while (iVar9 < 8);
    if ((local_34 != 8) && ((local_5 != '\0' || (local_30 <= 10.0)))) {
      local_c->stuckState = local_34 + 1;
      return;
    }
    local_c->stuckState = 9;
    return;
  }
  if (iVar2 < 1) {
    return;
  }
  if (iVar2 < 9) {
    fVar16 = Get_Time();
    pUVar13 = local_c;
    if (local_c->nextStuck < fVar16) {
      if (local_5 == '\0') {
        local_c->stuckState = 9;
      }
      else {
        local_c->stuckState = 0;
      }
      goto LAB_0046bec3;
    }
    bVar6 = OnBlocked(pVVar8);
    if (!bVar6) goto LAB_0046bee4;
    (pVVar1->control).braccel = (float)stuckStateText[pUVar13->stuckState + 10];
    pVVar14->steer = 0.0;
    (pVVar1->control).turbo = (uint)(0.0 < (float)stuckStateText[pUVar13->stuckState + 10]);
    fVar16 = DirectionBraccel[pUVar13->stuckState + 7];
  }
  else {
    if (iVar2 == 9) {
      fVar16 = Get_Time();
      pUVar13 = local_c;
      if ((local_c->nextStuck < fVar16) || (bVar6 = OnBlocked(pVVar8), !bVar6)) {
LAB_0046bee4:
        pUVar13->nextState = 1;
        return;
      }
      if (local_5 == '\0') {
        local_24 = local_40.x;
        local_20 = local_40.z;
        (**(code **)(pUVar13->me->_padding_ + 0x88))(local_40.x,local_40.z);
        if (0.25 <= ABS(pVVar14->steer)) {
          fVar16 = 0.0;
        }
        else {
          fVar16 = 1.0;
        }
        (pVVar1->control).turbo = 0;
        (pVVar1->control).braccel = fVar16;
        return;
      }
      pUVar13->stuckState = 6;
LAB_0046bec3:
      fVar16 = Get_Time();
      pUVar13->nextStuck = fVar16 + 2.0;
      return;
    }
    if (iVar2 != 10) {
      return;
    }
    fVar16 = Get_Time();
    if (local_c->nextStuck < fVar16) {
      local_c->nextState = 1;
      return;
    }
    (pVVar1->control).turbo = 0;
    (pVVar1->control).braccel = -1.0;
    fVar16 = 0.0;
    pVVar14->steer = 0.0;
  }
  (pVVar1->control).strafe = fVar16;
  return;
}
