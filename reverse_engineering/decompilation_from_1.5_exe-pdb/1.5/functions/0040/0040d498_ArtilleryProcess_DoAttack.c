/*
 * Entry: 0040d498
 * Name: ArtilleryProcess::DoAttack
 * Namespace: ArtilleryProcess
 * Signature: void DoAttack(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::DoAttack(ArtilleryProcess *this)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D_LONG VVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  ArtilleryProcess *pAVar10;
  Mortar *pMVar11;
  bool bVar12;
  char cVar13;
  GameObject *pGVar14;
  int iVar15;
  Mortar *pMVar16;
  _OBJ76 *p_Var17;
  MAT_3D *pMVar18;
  VECTOR_3D *pVVar19;
  VECTOR_3D *pVVar20;
  float *pfVar21;
  int iVar22;
  int *piVar23;
  MAT_3D *pMVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  double dVar28;
  undefined4 uVar29;
  MAT_3D local_120;
  MAT_3D local_e0;
  double local_a0;
  double local_98;
  double local_90;
  float local_88;
  double local_84;
  double local_7c;
  double local_74;
  float local_6c;
  VECTOR_3D local_68;
  VECTOR_3D local_5c;
  int local_50;
  float local_4c;
  float local_48;
  float local_44;
  float *local_40;
  float local_3c;
  ArtilleryProcess *local_38;
  float local_34;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  Mortar *local_18;
  GameObject *local_14;
  int *local_10;
  Carrier *local_c;
  char local_5;
  
  local_38 = this;
  (**(code **)(*(int *)this->_padding_ + 0x84))(0);
  pGVar14 = GameObjectHandle::GetObj(this->_padding_);
  iVar22 = 0;
  local_14 = pGVar14;
  if (pGVar14 == (GameObject *)0x0) {
    Say((Craft *)this->_padding_,KILLED_MSG,((Craft *)this->_padding_)->_padding_);
    if ((((GameObject *)this->_padding_)->curCmd).what == CMD_ATTACK) {
      GameObject::ClearCommand((GameObject *)this->_padding_);
    }
    goto LAB_0040d4f5;
  }
  local_c = ((GameObject *)this->_padding_)->carrier;
  if ((local_c == (Carrier *)0x0) ||
     (bVar12 = GameObject::FriendP((GameObject *)this->_padding_,pGVar14), bVar12))
  goto LAB_0040d4f5;
  if (this->_padding_ == *(int *)(this->_padding_ + 0x1f0)) {
    local_10 = *(int **)(this->_padding_ + 500);
    fVar25 = Get_Time();
    if (fVar25 - (float)local_10 < 5.0) {
      fVar25 = Get_Time();
      this->attackTimeout = fVar25 + 30.0;
    }
  }
  iVar15 = GameObject::GetHandle((GameObject *)this->_padding_);
  if (pGVar14->who_shot_JR == iVar15) {
    local_10 = (int *)pGVar14->enemyShot;
    fVar25 = Get_Time();
    if (fVar25 - (float)local_10 < 5.0) {
      fVar25 = Get_Time();
      this->attackTimeout = fVar25 + 30.0;
    }
  }
  fVar25 = Get_Time();
  if (this->attackTimeout < fVar25) {
LAB_0040d5a1:
    Say((Craft *)this->_padding_,USER1_MSG,0);
LAB_0040d4f5:
    this->_padding_ = 3;
    return;
  }
  local_18 = (Mortar *)0x0;
  do {
    pMVar16 = (Mortar *)Carrier::GetWeapon(local_c,iVar22);
    pMVar11 = pMVar16;
    if (pMVar16 != (Mortar *)0x0) break;
    iVar22 = iVar22 + 1;
    pMVar16 = (Mortar *)0x0;
    pMVar11 = local_18;
  } while (iVar22 < 5);
  local_18 = pMVar11;
  piVar23 = &local_14->_padding_;
  local_10 = piVar23;
  p_Var17 = (_OBJ76 *)(**(code **)(*piVar23 + 0x30))();
  iVar22 = dynamic_object(p_Var17);
  if (iVar22 == 0) {
LAB_0040d611:
    local_5 = '\0';
  }
  else {
    p_Var17 = (_OBJ76 *)(**(code **)(*piVar23 + 0x30))();
    iVar22 = IsCraft(p_Var17);
    if ((iVar22 != 0) && (cVar13 = (**(code **)(local_14->_padding_ + 0x68))(), cVar13 == '\0'))
    goto LAB_0040d611;
    local_5 = '\x01';
  }
  local_40 = (float *)(*(int *)(this->_padding_ + 0x228) + 0xc4);
  local_c = (Carrier *)CONCAT31(local_c._1_3_,1);
  pMVar18 = Matrix_Multiply(&local_120,&(*(_OBJ76 **)&pMVar16->field_0x10)->transform,
                            (MAT_3D *)&pMVar16->field_0x20);
  local_50 = 0;
  pMVar24 = &local_e0;
  for (iVar22 = 0x10; pMVar11 = local_18, pAVar10 = local_38, iVar22 != 0; iVar22 = iVar22 + -1) {
    pMVar24->right_x = pMVar18->right_x;
    pMVar18 = (MAT_3D *)&pMVar18->right_y;
    pMVar24 = (MAT_3D *)&pMVar24->right_y;
  }
  if (*(int *)(*(int *)&local_18->field_0x8 + 0xc) == 0x4d4f5254) {
    bVar12 = MayHitFriends((GameObject *)local_38->_padding_,(float)local_38->_padding_,0.3,1.0);
    if (bVar12) {
      local_c = (Carrier *)((uint)local_c & 0xffffff00);
    }
    bVar12 = Mortar::GetLeadPosition(pMVar11,&local_68,&local_88,local_14,SUB41(local_c,0));
    if (!bVar12) {
      Say((Craft *)pAVar10->_padding_,USER1_MSG,0);
      pAVar10->_padding_ = 3;
      return;
    }
    local_30.x = local_68.x - (float)*(double *)&pMVar16->field_0x48;
    local_30.y = local_68.y - (float)*(double *)&pMVar16->field_0x50;
    local_30.z = local_68.z - (float)*(double *)&pMVar16->field_0x58;
    local_24 = local_30.x;
    local_20 = local_30.y;
    local_1c = local_30.z;
    pVVar19 = Normalize_Vector(&local_5c,&local_30);
    local_3c = SQRT(local_88);
    local_30.x = pVVar19->x;
    local_30.y = pVVar19->y;
    local_30.z = pVVar19->z;
    local_84 = local_e0.posit_x;
    local_a0 = local_e0.posit_x;
    local_7c = local_e0.posit_y;
    local_98 = local_e0.posit_y;
    local_74 = local_e0.posit_z;
    local_90 = local_e0.posit_z;
    pVVar19 = ScaleVector(&local_5c,*(float *)(*(int *)&local_18->field_0xc + 0x50),*pVVar19);
    local_24 = pVVar19->x;
    local_20 = pVVar19->y;
    local_1c = pVVar19->z;
    for (; 0.0 < local_3c; local_3c = local_3c - local_34) {
      local_6c = Min(local_3c,1.0);
      local_20 = local_20 - local_6c * 4.9;
      local_4c = local_24 * local_6c + (float)local_84;
      local_84 = (double)local_4c;
      local_48 = local_20 * local_6c + (float)local_7c;
      local_7c = (double)local_48;
      local_44 = local_1c * local_6c + (float)local_74;
      local_74 = (double)local_44;
      local_20 = local_20 - local_6c * 4.9;
      local_4c = local_4c - (float)local_a0;
      local_48 = local_48 - (float)local_98;
      local_44 = local_44 - (float)local_90;
      VVar1.y._0_4_ = SUB84(local_98,0);
      VVar1.x = local_a0;
      VVar1.y._4_4_ = (int)((ulonglong)local_98 >> 0x20);
      VVar1.z._0_4_ = SUB84(local_90,0);
      VVar1.z._4_4_ = (int)((ulonglong)local_90 >> 0x20);
      VVar6.y = local_48;
      VVar6.x = local_4c;
      VVar6.z = local_44;
      local_34 = local_6c;
      iVar22 = Terrain_GetIntersection(VVar1,VVar6,&local_6c,(VECTOR_3D *)0x0);
      if (iVar22 != 0) {
        local_50 = 1;
        break;
      }
      local_a0 = local_84;
      local_98 = local_7c;
      local_90 = local_74;
    }
  }
  else {
    pfVar21 = (float *)(**(code **)(*(int *)local_18 + 0x2c))(&local_5c,local_14);
    local_68.x = *pfVar21;
    local_68.y = pfVar21[1];
    local_68.z = pfVar21[2];
    local_4c = *pfVar21;
    local_48 = pfVar21[1];
    local_44 = pfVar21[2];
    local_30.x = local_4c - (float)*(double *)&pMVar16->field_0x48;
    local_30.y = local_48 - (float)*(double *)&pMVar16->field_0x50;
    local_30.z = local_44 - (float)*(double *)&pMVar16->field_0x58;
    local_34 = 1.0;
    VVar2.y._4_4_ = (int)((ulonglong)*(double *)&pMVar16->field_0x50 >> 0x20);
    VVar2._0_12_ = *(undefined1 (*) [12])&pMVar16->field_0x48;
    VVar2.z._0_4_ = SUB84(*(double *)&pMVar16->field_0x58,0);
    VVar2.z._4_4_ = (int)((ulonglong)*(double *)&pMVar16->field_0x58 >> 0x20);
    VVar7.y = local_30.y;
    VVar7.x = local_30.x;
    VVar7.z = local_30.z;
    local_24 = local_30.x;
    local_20 = local_30.y;
    local_1c = local_30.z;
    Terrain_GetIntersection(VVar2,VVar7,&local_34,(VECTOR_3D *)0x0);
    pVVar19 = Normalize_Vector(&local_5c,&local_30);
    local_30.x = pVVar19->x;
    local_30.y = pVVar19->y;
    local_30.z = pVVar19->z;
  }
  if (((*(int *)(*(int *)&local_18->field_0x8 + 0xc) == 0x4d4f5254) && ((char)local_c != '\0')) &&
     (local_50 != 0)) {
    bVar12 = Mortar::GetLeadPosition(local_18,&local_68,&local_6c,local_14,false);
    this = local_38;
    if (!bVar12) goto LAB_0040d5a1;
    local_30.x = local_68.x - (float)*(double *)&pMVar16->field_0x48;
    local_30.y = local_68.y - (float)*(double *)&pMVar16->field_0x50;
    local_30.z = local_68.z - (float)*(double *)&pMVar16->field_0x58;
    local_34 = 1.0;
    VVar3.y._4_4_ = (int)((ulonglong)*(double *)&pMVar16->field_0x50 >> 0x20);
    VVar3._0_12_ = *(undefined1 (*) [12])&pMVar16->field_0x48;
    VVar3.z._0_4_ = SUB84(*(double *)&pMVar16->field_0x58,0);
    VVar3.z._4_4_ = (int)((ulonglong)*(double *)&pMVar16->field_0x58 >> 0x20);
    VVar8.y = local_30.y;
    VVar8.x = local_30.x;
    VVar8.z = local_30.z;
    local_24 = local_30.x;
    local_20 = local_30.y;
    local_1c = local_30.z;
    local_50 = Terrain_GetIntersection(VVar3,VVar8,&local_34,(VECTOR_3D *)0x0);
    pVVar19 = Normalize_Vector(&local_5c,&local_30);
    local_30.x = pVVar19->x;
    local_30.y = pVVar19->y;
    local_30.z = pVVar19->z;
  }
  pVVar19 = Vector_Unrotate(&local_5c,&local_30,&local_e0);
  local_30.x = pVVar19->x;
  local_30.y = pVVar19->y;
  local_30.z = pVVar19->z;
  fVar25 = Clamp(local_30.x * -2.5,-1.0,1.0);
  pfVar21 = local_40;
  *local_40 = fVar25;
  local_40 = (float *)Clamp(local_30.y * 2.5,-1.0,1.0);
  fVar25 = TimeStep();
  pMVar16 = local_18;
  pfVar21[1] = fVar25 * (float)local_40 + fVar25 * (float)local_40 + pfVar21[1];
  if (*(int *)(*(int *)&local_18->field_0xc + 0xc) == 0x504f5052) {
    pVVar19 = (VECTOR_3D *)(**(code **)(*local_10 + 0xc))();
    pVVar20 = (VECTOR_3D *)(**(code **)(*(int *)(local_38->_padding_ + 0x20) + 0xc))();
    fVar26 = Dist3D_Squared(*pVVar20,*pVVar19);
    fVar25 = *(float *)(*(int *)&pMVar16->field_0xc + 0xb0);
    if (fVar25 * fVar25 <= fVar26) {
      return;
    }
  }
  else {
    if ((*(int *)(*(int *)&local_18->field_0x8 + 0xc) == 0x52444554) &&
       (local_18[1].field_0x10 != '\0')) {
      iVar22 = *(int *)(local_18 + 1);
      if (iVar22 == 0) {
        return;
      }
      iVar15 = *(int *)(iVar22 + 0x18);
      local_4c = (float)*(double *)(iVar15 + 0x48);
      local_40 = (float *)(iVar22 + 0x34);
      local_48 = (float)*(double *)(iVar15 + 0x50);
      local_44 = (float)*(double *)(iVar15 + 0x58);
      fVar25 = *local_40;
      uVar29 = *(undefined4 *)(iVar22 + 0x38);
      fVar26 = *(float *)(iVar22 + 0x3c);
      fVar27 = TimeStep();
      VVar4.y = local_48;
      VVar4.x = local_4c;
      VVar4.z = local_44;
      VVar9.y = (float)uVar29;
      VVar9.x = fVar25;
      VVar9.z = fVar26;
      pVVar19 = AddMultVectors(&local_5c,VVar4,fVar27,VVar9);
      local_24 = pVVar19->x;
      local_20 = pVVar19->y;
      local_1c = pVVar19->z;
      iVar22 = *(int *)(*(int *)(iVar22 + 0x10) + 0x3c);
      if (iVar22 != 0) {
        pVVar19 = (VECTOR_3D *)(**(code **)(*(int *)(local_38->_padding_ + 0x20) + 0xc))();
        local_c = *(Carrier **)(iVar22 + 0x50);
        VVar5.y = local_20;
        VVar5.x = local_24;
        VVar5.z = local_1c;
        fVar25 = Dist3D_Squared(VVar5,*pVVar19);
        if (fVar25 < (float)local_c * (float)local_c) {
          return;
        }
      }
      local_5c.x = *local_40;
      local_5c.y = local_40[1];
      local_5c.z = local_40[2];
      local_4c = (local_14->euler).v.x;
      local_48 = (local_14->euler).v.y;
      local_44 = (local_14->euler).v.z;
      local_30.x = local_4c - local_5c.x;
      local_30.y = local_48 - local_5c.y;
      local_30.z = local_44 - local_5c.z;
      pfVar21 = (float *)(**(code **)(*local_10 + 0xc))();
      local_5c.x = *pfVar21;
      local_5c.y = pfVar21[1];
      local_5c.z = pfVar21[2];
      if ((local_5c.x - local_24) * local_30.x +
          (local_5c.y - local_20) * local_30.y + (local_5c.z - local_1c) * local_30.z <= 0.0) {
        return;
      }
      iVar22 = *(int *)local_18;
      goto LAB_0040dc21;
    }
    if (local_50 != 0) {
      return;
    }
    if (((char)local_c == '\0') || (local_5 == '\0')) {
      dVar28 = 0.0010000000474974513;
      if (0.001 <= ABS(local_30.x)) {
        return;
      }
    }
    else {
      pVVar19 = (VECTOR_3D *)(**(code **)(*local_10 + 0xc))();
      pVVar20 = (VECTOR_3D *)(**(code **)(*(int *)(local_38->_padding_ + 0x20) + 0xc))();
      fVar25 = Dist3D_Squared(*pVVar20,*pVVar19);
      dVar28 = rsqrt((double)(fVar25 + 0.0001));
      dVar28 = dVar28 * (double)local_14->collisionRadius * 0.5;
      if (dVar28 <= ABS((double)local_30.x)) {
        return;
      }
    }
    if (dVar28 <= ABS((double)local_30.y)) {
      return;
    }
  }
  iVar22 = *(int *)pMVar16;
LAB_0040dc21:
  (**(code **)(iVar22 + 8))();
  return;
}
