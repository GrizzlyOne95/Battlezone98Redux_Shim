/*
 * Entry: 0045a44d
 * Name: RecycleTask::DoStuck
 * Namespace: RecycleTask
 * Signature: void DoStuck(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoStuck(RecycleTask *this)

{
  VEHICLE *pVVar1;
  int iVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D_LONG VVar4;
  VHCL_CONTROL *pVVar5;
  bool bVar6;
  char cVar7;
  VECTOR_3D *pVVar8;
  int iVar9;
  Craft *pCVar10;
  _OBJ76 *p_Var11;
  VECTOR_3D *pVVar12;
  float *pfVar13;
  float fVar14;
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
  RecycleTask *local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_3D local_18;
  VHCL_CONTROL *local_c;
  char local_5;
  
  iVar9 = this->me->_padding_;
  pVVar1 = this->me->vhcl;
  local_58.x = *(double *)*(undefined1 (*) [12])(iVar9 + 0x48);
  local_58.y = *(double *)(iVar9 + 0x50);
  pVVar12 = (VECTOR_3D *)(iVar9 + 0x20);
  local_58.z = *(double *)(iVar9 + 0x58);
  local_c = &pVVar1->control;
  VVar4.y._4_4_ = (int)((ulonglong)local_58.y >> 0x20);
  VVar4._0_12_ = *(undefined1 (*) [12])(iVar9 + 0x48);
  VVar4.z._0_4_ = SUB84(local_58.z,0);
  VVar4.z._4_4_ = (int)((ulonglong)local_58.z >> 0x20);
  local_2c = this;
  Floor_GetFloor(VVar4,&local_68,&local_40);
  fVar14 = Clamp((*(float *)(iVar9 + 0x40) * local_40.z +
                 *(float *)(iVar9 + 0x3c) * local_40.y + local_40.x * *(float *)(iVar9 + 0x38)) *
                 -1.0,-1.0,1.0);
  (pVVar1->control).pitch = fVar14;
  local_5 = 0.7 < local_40.y;
  pVVar8 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  iVar2 = this->stuckState;
  if (iVar2 == 0) {
    local_c->turbo = 0;
    local_c->braccel = -0.1;
    local_c->steer = 0.0;
    bVar6 = OnBlocked(pVVar8);
    if (bVar6) {
      fVar14 = Get_Time();
      this->nextStuck = fVar14 + 2.0;
      local_30 = 50.0;
      local_34 = 8;
      Range::Search(GameObject::objectRange,(double)(pVVar8->x - 50.0),(double)(pVVar8->z - 50.0),
                    (double)(pVVar8->x + 50.0),(double)(pVVar8->z + 50.0),&local_15c);
      local_e8.x = *(float *)(iVar9 + 0x38);
      local_e8.y = *(float *)(iVar9 + 0x3c);
      local_e8.z = *(float *)(iVar9 + 0x40);
      local_24 = pVVar12->x;
      local_20 = *(float *)(iVar9 + 0x24);
      local_1c = *(float *)(iVar9 + 0x28);
      local_18.x = ((VECTOR_3D *)(iVar9 + 0x38))->x;
      local_18.y = *(float *)(iVar9 + 0x3c);
      local_18.z = *(float *)(iVar9 + 0x40);
      pVVar8 = CombineVectors(&local_130,0.707107,*(VECTOR_3D *)(iVar9 + 0x38),0.707107,*pVVar12);
      local_d0 = pVVar12->x;
      local_dc = pVVar8->x;
      uStack_cc = *(undefined4 *)(iVar9 + 0x24);
      uStack_c8 = *(undefined4 *)(iVar9 + 0x28);
      fStack_d8 = pVVar8->y;
      local_18.x = pVVar12->x;
      fStack_d4 = pVVar8->z;
      local_18.y = *(float *)(iVar9 + 0x24);
      local_18.z = *(float *)(iVar9 + 0x28);
      local_24 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
      local_20 = *(float *)(iVar9 + 0x3c);
      local_1c = *(float *)(iVar9 + 0x40);
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
      local_24 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
      local_20 = *(float *)(iVar9 + 0x3c);
      fStack_b0 = pVVar8->z;
      local_1c = *(float *)(iVar9 + 0x40);
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
      local_24 = ((VECTOR_3D *)(iVar9 + 0x38))->x;
      local_20 = *(float *)(iVar9 + 0x3c);
      fStack_98 = pVVar8->z;
      local_1c = *(float *)(iVar9 + 0x40);
      pVVar8 = CombineVectors(&local_118,0.707107,*(VECTOR_3D *)(iVar9 + 0x38),-0.707107,*pVVar12);
      local_94 = pVVar8->x;
      fStack_90 = pVVar8->y;
      local_c = (VHCL_CONTROL *)0x0;
      fStack_8c = pVVar8->z;
      pVVar8 = &local_e8;
      do {
        local_28 = 50.0;
        VVar3.y._0_4_ = SUB84(local_58.y,0);
        VVar3.x = local_58.x;
        VVar3.y._4_4_ = (int)((ulonglong)local_58.y >> 0x20);
        VVar3.z._0_4_ = SUB84(local_58.z,0);
        VVar3.z._4_4_ = (int)((ulonglong)local_58.z >> 0x20);
        iVar9 = Terrain_GetIntersection(VVar3,*pVVar8,&local_28,&local_18);
        pVVar5 = local_c;
        if ((iVar9 == 0) || (fVar14 = local_28, 0.7 <= local_18.y)) {
          fVar14 = 50.0;
        }
        local_c = (VHCL_CONTROL *)((int)&local_c->steer + 1);
        local_88[(int)pVVar5] = fVar14;
        pVVar8 = pVVar8 + 1;
      } while ((int)local_c < 8);
      iVar9 = (**(code **)local_2c->me->_padding_)();
      local_64.x = (float)local_58.x;
      local_64.y = (*(float *)(iVar9 + 0x118) + *(float *)(iVar9 + 0x124)) * 0.5 + (float)local_58.y
      ;
      local_64.z = (float)local_58.z;
      local_1c = (*(float *)(iVar9 + 0x124) - *(float *)(iVar9 + 0x118)) * 0.5;
      while (bVar6 = Range_Search_Results::Get_Next_Object(&local_15c,(int **)&local_c), bVar6) {
        pCVar10 = (Craft *)GameObject::GetObj((int)local_c->steer);
        if ((pCVar10 != (Craft *)0x0) && (pCVar10 != local_2c->me)) {
          p_Var11 = (_OBJ76 *)(**(code **)(pCVar10->_padding_ + 0x30))();
          iVar9 = dynamic_object(p_Var11);
          if ((iVar9 == 0) ||
             ((iVar9 = IsCraft(p_Var11), iVar9 != 0 &&
              (cVar7 = (**(code **)(pCVar10->_padding_ + 100))(), cVar7 != '\0')))) {
            pVVar8 = &local_e8;
            pfVar13 = local_88;
            local_28 = 1.12104e-44;
            do {
              IntersectGameObject(&local_64,pVVar8,pfVar13,&local_18,(GameObject *)pCVar10,local_1c)
              ;
              pfVar13 = pfVar13 + 1;
              pVVar8 = pVVar8 + 1;
              local_28 = (float)((int)local_28 + -1);
            } while (local_28 != 0.0);
          }
        }
      }
      iVar9 = 0;
      pVVar8 = &local_e8;
      do {
        fVar14 = DistToOffBlocked(&local_58,pVVar8,local_88[iVar9]);
        if ((fVar14 < local_30) && (fVar14 < local_88[iVar9])) {
          local_30 = fVar14;
          local_34 = iVar9;
        }
        iVar9 = iVar9 + 1;
        pVVar8 = pVVar8 + 1;
      } while (iVar9 < 8);
      if ((local_34 != 8) && ((local_5 != '\0' || (local_30 <= 10.0)))) {
        local_2c->stuckState = local_34 + 1;
        return;
      }
      local_2c->stuckState = 9;
      return;
    }
    fVar14 = Get_Time();
    this->stuckState = 10;
LAB_0045aabb:
    this->nextStuck = fVar14 + 2.0;
  }
  else {
    if (iVar2 < 1) {
      return;
    }
    if (iVar2 < 9) {
      fVar14 = Get_Time();
      if (this->nextStuck < fVar14) {
        if (local_5 == '\0') {
          this->stuckState = 9;
        }
        else {
          this->stuckState = 0;
        }
LAB_0045a599:
        fVar14 = Get_Time();
        goto LAB_0045aabb;
      }
      bVar6 = OnBlocked(pVVar8);
      if (bVar6) {
        local_c->braccel = (float)stateText[this->stuckState + 8];
        local_c->steer = 0.0;
        local_c->turbo = (uint)(0.0 < (float)stateText[this->stuckState + 8]);
        local_c->strafe = DirectionBraccel[this->stuckState + 7];
        return;
      }
    }
    else if (iVar2 == 9) {
      fVar14 = Get_Time();
      if ((fVar14 <= this->nextStuck) && (bVar6 = OnBlocked(pVVar8), bVar6)) {
        if (local_5 == '\0') {
          local_20 = local_40.x;
          local_1c = local_40.z;
          (**(code **)(this->me->_padding_ + 0x88))(local_40.x,local_40.z);
          if (0.25 <= ABS(local_c->steer)) {
            fVar14 = 0.0;
          }
          else {
            fVar14 = 1.0;
          }
          local_c->turbo = 0;
          local_c->braccel = fVar14;
          return;
        }
        this->stuckState = 6;
        goto LAB_0045a599;
      }
    }
    else {
      if (iVar2 != 10) {
        return;
      }
      fVar14 = Get_Time();
      if (fVar14 <= this->nextStuck) {
        local_c->turbo = 0;
        local_c->braccel = -1.0;
        local_c->steer = 0.0;
        local_c->strafe = 0.0;
        return;
      }
    }
    this->nextState = 0;
  }
  return;
}
