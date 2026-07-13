/*
 * Entry: 00538e78
 * Name: SeismicWave::Simulate
 * Namespace: SeismicWave
 * Signature: void Simulate(SeismicWave * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SeismicWave::Simulate(SeismicWave *this,float param_1)

{
  uint *puVar1;
  short sVar2;
  ushort uVar3;
  float fVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  VECTOR_3D VVar10;
  double dVar11;
  int *piVar12;
  GameObject *pGVar13;
  bool bVar14;
  int iVar15;
  MAT_3D *pMVar16;
  ushort *puVar17;
  VECTOR_3D *pVVar18;
  SPHERE *pSVar19;
  _OBJ76 *p_Var20;
  tagENTITY *ptVar21;
  VECTOR_3D *pVVar22;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  float *pfVar23;
  MAT_3D *pMVar24;
  int *piVar25;
  float10 fVar26;
  float10 fVar27;
  float10 fVar28;
  float fVar29;
  MAT_3D *__return_storage_ptr__;
  MAT_3D local_224;
  Range_Search_Results local_1e4;
  VECTOR_3D local_1b8;
  VECTOR_3D local_1ac;
  VECTOR_3D local_1a0;
  VECTOR_3D local_194;
  VECTOR_3D local_188;
  VECTOR_3D local_17c;
  VECTOR_3D local_170;
  VECTOR_3D local_164;
  VECTOR_3D local_158;
  VECTOR_3D local_14c;
  VECTOR_3D local_140;
  int local_134;
  int iStack_130;
  int iStack_12c;
  float local_128;
  MAT_3D local_124;
  double local_e4;
  double local_dc;
  double local_d4;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  VECTOR_3D local_b4;
  int local_a8;
  float local_a4;
  undefined8 local_a0;
  VECTOR_3D local_98;
  VECTOR_3D local_8c;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  undefined8 local_70;
  double local_68;
  double local_60;
  undefined8 local_58;
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  int *local_34;
  float local_30;
  float local_2c;
  float local_28;
  VECTOR_3D local_24;
  undefined8 local_18;
  int *local_10;
  GameObject *local_c;
  short *local_8;
  
  local_a8 = Set_Rounding((int)unaff_EDI);
  if ((float)this->_padding_ < param_1) {
    param_1 = (float)this->_padding_;
  }
  if (0.0 < (float)this->_padding_) {
    iVar15 = this->_padding_;
    fVar29 = 1.0;
    if (*(float *)(iVar15 + 0x8c) <= (float)this->_padding_) {
      fVar4 = *(float *)(iVar15 + 0x88) * param_1 + this->scale;
      this->scale = fVar4;
      if (fVar4 <= 1.0) goto LAB_00538f21;
    }
    else {
      fVar4 = this->scale - *(float *)(iVar15 + 0x90) * param_1;
      this->scale = fVar4;
      fVar29 = 0.0;
      if (0.0 <= fVar4) goto LAB_00538f21;
    }
    this->scale = fVar29;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
LAB_00538f21:
  local_8 = this->deltaH;
  iVar15 = (this->zMin).i;
  local_18 = (double)CONCAT44(iVar15,(undefined4)local_18);
  while (iVar15 <= (this->zMax).i) {
    for (local_10 = (int *)(this->xMin).i; (int)local_10 <= (this->xMax).i;
        local_10 = (int *)((int)local_10 + 1)) {
      puVar17 = GetZonePtr((int)local_10,(int)local_18._4_4_);
      sVar2 = *local_8;
      local_8 = local_8 + 1;
      iVar15 = (*puVar17 & 0xfff) - (int)sVar2;
      if (iVar15 < 0) {
        iVar15 = 0;
      }
      else if (0xfff < iVar15) {
        iVar15 = 0xfff;
      }
      *puVar17 = (*puVar17 & 0xf000) + (short)iVar15;
    }
    iVar15 = (int)local_18._4_4_ + 1;
    local_18 = (double)CONCAT44(iVar15,(undefined4)local_18);
  }
  RemoveCoplanarFlags((this->xMin).i,(this->zMin).i,(this->xMax).i,(this->zMax).i);
  iVar15 = this->_padding_;
  local_7c = *(float *)(iVar15 + 0x38);
  local_78 = *(float *)(iVar15 + 0x3c);
  local_74 = *(float *)(iVar15 + 0x40);
  local_60 = *(double *)(iVar15 + 0x50);
  local_68 = (double)local_7c * (double)param_1 * (double)*(float *)(this->_padding_ + 0x50) +
             *(double *)(iVar15 + 0x48);
  local_58 = (double)local_74 * (double)param_1 * (double)*(float *)(this->_padding_ + 0x50) +
             *(double *)(iVar15 + 0x58);
  local_30 = local_7c;
  local_2c = local_78;
  local_28 = local_74;
  iVar15 = Terrain_ValidPoint(local_68,local_58);
  if (iVar15 == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
  else {
    Terrain_GetHeightAndNormal(local_68,local_58,&local_a4,&local_140);
    __return_storage_ptr__ = &local_224;
    local_60 = (double)local_a4;
    pMVar16 = Build_Orthogonal_Matrix(__return_storage_ptr__,unaff_EDI,unaff_ESI);
    dVar11 = local_68;
    pMVar24 = &local_124;
    for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
      pMVar24->right_x = pMVar16->right_x;
      pMVar16 = (MAT_3D *)&pMVar16->right_y;
      pMVar24 = (MAT_3D *)&pMVar24->right_y;
    }
    pMVar16 = &local_124;
    pfVar23 = (float *)(this->_padding_ + 0x20);
    for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
      *pfVar23 = pMVar16->right_x;
      pMVar16 = (MAT_3D *)&pMVar16->right_y;
      pfVar23 = pfVar23 + 1;
    }
    iVar15 = this->_padding_;
    *(double *)(iVar15 + 0x48) = dVar11;
    *(double *)(iVar15 + 0x50) = local_60;
    *(double *)(iVar15 + 0x58) = local_58;
    iVar15 = this->_padding_;
    local_7c = *(float *)(iVar15 + 0x38);
    local_78 = *(float *)(iVar15 + 0x3c);
    local_74 = *(float *)(iVar15 + 0x40);
    local_30 = local_7c;
    local_2c = local_78;
    local_28 = local_74;
    UpdateExtents(this);
    local_8 = this->deltaH;
    local_38 = *(float *)(this->_padding_ + 0x7c) * this->scale * 10.0;
    for (local_c = (GameObject *)(this->zMin).i; (int)local_c <= (this->zMax).i;
        local_c = (GameObject *)((int)&local_c->_padding_ + 1)) {
      iVar15 = (this->xMin).i;
      local_18 = (double)CONCAT44(iVar15,(undefined4)local_18);
      if (iVar15 <= (this->xMax).i) {
        local_70 = (double)CONCAT44((float)(int)local_c,(undefined4)local_70);
        do {
          puVar17 = GetZonePtr(iVar15,(int)local_c);
          iVar15 = this->_padding_;
          uVar3 = *puVar17;
          local_34 = (int *)(uVar3 & 0xfff);
          fVar28 = ((float10)(int)local_18._4_4_ * (float10)Terrain.Grid_Size - (float10)local_68) *
                   (float10)*(float *)(iVar15 + 0x74);
          fVar26 = ((float10)(int)local_34 * (float10)0.1 - (float10)local_60) *
                   (float10)*(float *)(iVar15 + 0x74);
          fVar27 = ((float10)(float)local_70._4_4_ * (float10)Terrain.Grid_Size - (float10)local_58)
                   * (float10)*(float *)(iVar15 + 0x74);
          fVar26 = fVar28 * fVar28 + fVar27 * fVar27 + fVar26 * fVar26;
          fVar28 = (float10)1;
          if (fVar28 < fVar26 == (fVar28 == fVar26)) {
            fVar26 = (float10)fcos(SQRT(fVar26) * (float10)3.1415927);
            local_a0 = (double)((fVar26 + fVar28) * (float10)0.5 * (float10)local_38 +
                               (float10)Float2Int);
            iVar15 = (int)local_a0 + (int)local_34;
            if (iVar15 < 0) {
              iVar15 = 0;
            }
            else if (0xfff < iVar15) {
              iVar15 = 0xfff;
            }
            *local_8 = (short)iVar15 - (short)local_34;
            *puVar17 = (uVar3 & 0xf000) + (short)iVar15;
          }
          else {
            *local_8 = 0;
          }
          local_8 = local_8 + 1;
          iVar15 = (int)local_18._4_4_ + 1;
          local_18 = (double)CONCAT44(iVar15,(undefined4)local_18);
        } while (iVar15 <= (this->xMax).i);
      }
    }
    RemoveCoplanarFlags((this->xMin).i,(this->zMin).i,(this->xMax).i,(this->zMax).i);
    iVar15 = this->_padding_;
    local_30 = *(float *)(iVar15 + 0x2c);
    local_2c = *(float *)(iVar15 + 0x30);
    local_28 = *(float *)(iVar15 + 0x34);
    iVar15 = this->_padding_;
    local_e4 = (double)(*(float *)(iVar15 + 0x70) * local_7c * 0.5 + (float)local_68);
    local_dc = (double)(*(float *)(iVar15 + 0x70) * local_78 * 0.5 + (float)local_60);
    local_d4 = (double)(*(float *)(iVar15 + 0x70) * local_74 * 0.5 + (float)local_58);
    local_80 = param_1;
    if (0.2 < param_1) {
      local_80 = 0.2;
    }
    iVar15 = this->_padding_;
    fVar29 = Get_Time();
    local_a0 = (double)CONCAT44(fVar29 * *(float *)(iVar15 + 0x9c),(int)local_a0);
    Range::Search(GameObject::objectRange,local_e4,local_d4,
                  (double)(*(float *)(iVar15 + 0x70) * 1.5 + 20.0),&local_1e4);
    while (bVar14 = Range_Search_Results::Get_Next_Object(&local_1e4,&local_34), bVar14) {
      local_c = GameObject::GetObj(*local_34);
      if (local_c != (GameObject *)0x0) {
        p_Var20 = local_c->obj;
        local_44 = (float)((float10)local_e4 - (float10)(p_Var20->transform).posit_x);
        local_40 = (float)((float10)local_dc - (float10)(p_Var20->transform).posit_y);
        local_3c = (float)((float10)local_d4 - (float10)(p_Var20->transform).posit_z);
        local_70 = (double)CONCAT44(&p_Var20->transform,(undefined4)local_70);
        fVar29 = local_2c * local_40 + local_28 * local_3c + local_30 * local_44;
        VVar5.y = local_40;
        VVar5.x = local_44;
        VVar5.z = local_3c;
        VVar8.y = local_2c;
        VVar8.x = local_30;
        VVar8.z = local_28;
        pVVar18 = AddMultVectors(&local_1a0,VVar5,fVar29 + fVar29,VVar8);
        pGVar13 = local_c;
        local_44 = pVVar18->x;
        local_40 = pVVar18->y;
        local_3c = pVVar18->z;
        iVar15 = this->_padding_;
        local_10 = (int *)(local_44 * local_44 + local_40 * local_40 + local_3c * local_3c);
        pSVar19 = GameObject::GetSphere(local_c);
        fVar29 = *(float *)(iVar15 + 0x70) * 1.5 + pSVar19->radius;
        if ((float)local_10 <= fVar29 * fVar29) {
          fVar28 = (float10)__CIexp();
          local_10 = &pGVar13->_padding_;
          local_8 = (short *)(float)(fVar28 * (float10)this->scale * (float10)local_80);
          iVar15 = (**(code **)*local_10)();
          iVar15 = *(int *)(iVar15 + 0x28);
          if (((iVar15 == 1) || (iVar15 == 6)) || (iVar15 == 3)) {
            local_60 = *(double *)&this->_padding_;
            local_58 = (double)CONCAT44((float)this->_padding_ * (float)local_8,this->_padding_);
            pVVar18 = Terrain_GetNormal(&local_158,
                                        (double)CONCAT44((int)*(undefined8 *)
                                                               ((int)local_70._4_4_ + 0x38),
                                                         (int)((ulonglong)
                                                               *(undefined8 *)
                                                                ((int)local_70._4_4_ + 0x28) >> 0x20
                                                              )),
                                        (double)CONCAT44(__return_storage_ptr__,
                                                         (int)((ulonglong)
                                                               *(undefined8 *)
                                                                ((int)local_70._4_4_ + 0x38) >> 0x20
                                                              )));
            local_50.x = pVVar18->x;
            local_50.y = pVVar18->y;
            local_50.z = pVVar18->z;
            local_98.x = local_50.x + local_7c;
            local_98.y = local_50.y + local_78 + 1.0;
            local_98.z = local_50.z + local_74;
            pVVar18 = Normalize_Vector(&local_170,&local_98);
            local_98.x = pVVar18->x;
            local_98.y = pVVar18->y;
            local_98.z = pVVar18->z;
            (**(code **)(*local_10 + 0x38))(&local_60,&local_98);
            local_18 = (double)CONCAT44((float)local_c->seqNo + local_a0._4_4_,(undefined4)local_18)
            ;
            VVar7.y = local_98.y;
            VVar7.x = local_98.x;
            VVar7.z = local_98.z;
            pVVar18 = ScaleVector(&local_188,*(float *)(this->_padding_ + 0x94) * (float)local_8,
                                  VVar7);
            local_24.x = pVVar18->x;
            local_24.y = pVVar18->y;
            local_24.z = pVVar18->z;
            pVVar18 = Cross_Product(&local_1ac,&local_50,&local_24);
            local_24.x = pVVar18->x;
            local_24.y = pVVar18->y;
            local_24.z = pVVar18->z;
            pVVar18 = Vector_Unrotate(&local_164,&local_24,local_70._4_4_);
            local_24.x = pVVar18->x;
            local_24.y = pVVar18->y;
            local_24.z = pVVar18->z;
            fVar29 = Noise1D(local_18._4_4_ + 8.53);
            local_24.x = fVar29 * *(float *)(this->_padding_ + 0xa0) * (float)local_8 + local_24.x;
            fVar29 = Noise1D(local_18._4_4_ + 17.67);
            local_24.y = fVar29 * *(float *)(this->_padding_ + 0xa0) * (float)local_8 * 0.5 +
                         local_24.y;
            fVar29 = Noise1D(local_18._4_4_ + 5.19);
            local_24.z = fVar29 * *(float *)(this->_padding_ + 0xa0) * (float)local_8 + local_24.z;
            iVar15 = (**(code **)*local_10)();
            if (*(int *)(iVar15 + 0x20) == 0x54555252) {
              fVar29 = *(float *)(this->_padding_ + 0xac);
              pVVar18 = &local_17c;
LAB_005396f6:
              VVar9.y = local_24.y;
              VVar9.x = local_24.x;
              VVar9.z = local_24.z;
              pVVar18 = ScaleVector(pVVar18,fVar29,VVar9);
              local_24.x = pVVar18->x;
              local_24.y = pVVar18->y;
              local_24.z = pVVar18->z;
            }
            else if (*(int *)(iVar15 + 0x20) == 0x57414c4b) {
              fVar29 = *(float *)(this->_padding_ + 0xa8);
              pVVar18 = &local_14c;
              goto LAB_005396f6;
            }
            VVar6.y = local_24.y;
            VVar6.x = local_24.x;
            VVar6.z = local_24.z;
            pVVar22 = AddMultVectors(&local_1b8,VVar6,
                                     -(*(float *)(this->_padding_ + 0xb0) * (float)local_8),
                                     (local_c->euler).omega);
            p_Var20 = local_c->obj;
            local_24.y = pVVar22->y;
            local_24.x = pVVar22->x -
                         ((p_Var20->transform).front_x * local_50.x +
                         (p_Var20->transform).front_y * local_50.y +
                         (p_Var20->transform).front_z * local_50.z) * (float)local_8 *
                         *(float *)(this->_padding_ + 0xb4);
            pVVar18 = &(local_c->euler).omega;
            local_cc = pVVar18->x;
            local_24.z = ((p_Var20->transform).right_x * local_50.x +
                         (p_Var20->transform).right_y * local_50.y +
                         (p_Var20->transform).right_z * local_50.z) * (float)local_8 *
                         *(float *)(this->_padding_ + 0xb4) + pVVar22->z;
            local_c8 = (local_c->euler).omega.y;
            local_c4 = (local_c->euler).omega.z;
            local_c0 = local_cc + local_24.x;
            local_bc = local_c8 + local_24.y;
            local_b8 = local_c4 + local_24.z;
            pVVar18->x = local_c0;
            (local_c->euler).omega.y = local_bc;
            (local_c->euler).omega.z = local_b8;
            VVar10.y = local_98.y;
            VVar10.x = local_98.x;
            VVar10.z = local_98.z;
            pVVar18 = ScaleVector(&local_194,*(float *)(this->_padding_ + 0x98) * (float)local_8,
                                  VVar10);
            local_8c.x = pVVar18->x;
            local_8c.y = pVVar18->y;
            local_8c.z = pVVar18->z;
            fVar29 = Noise1D(local_18._4_4_);
            local_8c.x = fVar29 * *(float *)(this->_padding_ + 0xa4) * (float)local_8 + local_8c.x;
            fVar29 = Noise1D(local_18._4_4_ + 2.27);
            local_8c.y = fVar29 * *(float *)(this->_padding_ + 0xa4) * (float)local_8 * 0.5 +
                         local_8c.y;
            fVar29 = Noise1D(local_18._4_4_ + 23.41);
            local_8c.z = fVar29 * *(float *)(this->_padding_ + 0xa4) * (float)local_8 + local_8c.z;
            GameObject::AddVelocity(local_c,&local_8c);
          }
          else if (((iVar15 == 2) || (iVar15 == 10)) || ((iVar15 == 7 || (iVar15 == 5)))) {
            local_134 = this->_padding_;
            iStack_130 = this->_padding_;
            iStack_12c = this->_padding_;
            local_128 = *(float *)(this->_padding_ + 0xb8) * (float)local_8 * (float)this->_padding_
            ;
            (**(code **)(*local_10 + 0x38))(&local_134,&local_140);
            pMVar16 = &local_c->obj->transform;
            pMVar24 = &local_124;
            for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
              pMVar24->right_x = pMVar16->right_x;
              pMVar16 = (MAT_3D *)&pMVar16->right_y;
              pMVar24 = (MAT_3D *)&pMVar24->right_y;
            }
            local_70 = local_124.posit_x;
            local_18 = local_124.posit_z;
            Terrain_GetHeightAndNormal(local_124.posit_x,local_124.posit_z,&local_38,&local_b4);
            if (((0.01 < ABS((float)local_124.posit_y - local_38)) ||
                (0.001 < ABS(local_124.up_x - local_b4.x))) ||
               (0.001 < ABS(local_124.up_z - local_b4.z))) {
              pMVar16 = Build_Orthogonal_Matrix
                                  (&local_224,(VECTOR_3D *)__return_storage_ptr__,unaff_EDI);
              local_124.posit_x = local_70;
              pMVar24 = &local_124;
              for (iVar15 = 0x10; pGVar13 = local_c, iVar15 != 0; iVar15 = iVar15 + -1) {
                pMVar24->right_x = pMVar16->right_x;
                pMVar16 = (MAT_3D *)&pMVar16->right_y;
                pMVar24 = (MAT_3D *)&pMVar24->right_y;
              }
              local_124.posit_y = (double)local_38;
              local_124.posit_z = local_18;
              GameObject::SetTransform(local_c,&local_124);
              piVar12 = local_10;
              pMVar16 = &local_124;
              piVar25 = &pGVar13->_padding_;
              for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
                *piVar25 = (int)pMVar16->right_x;
                pMVar16 = (MAT_3D *)&pMVar16->right_y;
                piVar25 = piVar25 + 1;
              }
              p_Var20 = (_OBJ76 *)(**(code **)(*local_10 + 0x30))();
              iVar15 = OwnsFloor(p_Var20);
              if (iVar15 != 0) {
                ptVar21 = (tagENTITY *)(**(code **)(*piVar12 + 0x2c))();
                Floor_ClearEntity(ptVar21);
                ptVar21 = (tagENTITY *)(**(code **)(*piVar12 + 0x2c))();
                Floor_InitEntity(ptVar21);
              }
            }
          }
        }
      }
    }
    this->_padding_ = (int)((float)this->_padding_ - param_1);
    Set_Rounding((int)__return_storage_ptr__);
  }
  return;
}
