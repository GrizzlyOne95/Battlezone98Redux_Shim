
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall HoverCraft::UpdateGimbals(HoverCraft *this,float param_1)

{
  float fVar1;
  int iVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  float fVar8;
  uint uVar9;
  int iVar10;
  MAT_3D *pMVar11;
  _OBJ76 *p_Var12;
  VECTOR_3D *pVVar13;
  VECTOR_3D *unaff_ESI;
  MAT_3D *pMVar14;
  float *pfVar15;
  ushort uVar16;
  float fVar17;
  MAT_3D local_314;
  MAT_3D local_2d4;
  MAT_3D local_294;
  MAT_3D local_254;
  MAT_3D local_214;
  float afStack_1d4 [8];
  MAT_3D local_1b4;
  float local_174 [10];
  double local_14c;
  double local_144;
  double local_13c;
  MAT_3D local_134;
  MAT_3D local_f4;
  MAT_3D local_b4;
  double local_74;
  undefined1 local_6c [8];
  double local_64;
  VECTOR_3D local_5c;
  float local_50;
  float local_4c;
  float local_48;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  float local_20;
  int local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
  iVar10 = this->_padding_;
  local_18 = *(float *)(iVar10 + 0xc4);
  local_c = ___real_3fc00000;
  if (*(int *)(iVar10 + 0xd4) == 0) {
    local_c = *(float *)(iVar10 + 0xd0);
  }
  local_4c = *(float *)(iVar10 + 0xcc);
  iVar2 = this->_padding_;
  uVar9 = (uint)(*(int *)(iVar10 + 0xd8) != 0);
  local_10 = 0.0;
  local_1c = 0;
  local_48 = *(float *)(iVar2 + 0x34c + uVar9 * 4);
  local_50 = *(float *)(iVar2 + 0x354 + uVar9 * 4);
  local_20 = *(float *)(iVar2 + 0x35c + uVar9 * 4);
  local_14 = *(float *)(iVar2 + 0x364 + uVar9 * 4);
  fVar17 = (float)this->_padding_;
  do {
    iVar10 = *(int *)((int)fVar17 + 0xac);
    local_8 = fVar17;
    if (iVar10 == 0x42) {
      pMVar11 = Build_Roll_Matrix(&local_294,
                                  (-*(float *)((int)fVar17 + 0x24) - local_48 * local_4c) * param_1
                                  * ___real_40400000);
      pMVar14 = &local_f4;
      for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
        pMVar14->right_x = pMVar11->right_x;
        pMVar11 = (MAT_3D *)&pMVar11->right_y;
        pMVar14 = (MAT_3D *)&pMVar14->right_y;
      }
      pMVar14 = (MAT_3D *)((int)local_8 + 0x20);
      pMVar11 = &local_134;
LAB_0049d268:
      pMVar11 = Matrix_Multiply(pMVar11,&local_f4,pMVar14);
      for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
        pMVar14->right_x = pMVar11->right_x;
        pMVar11 = (MAT_3D *)&pMVar11->right_y;
        pMVar14 = (MAT_3D *)&pMVar14->right_y;
      }
    }
    else {
      if (iVar10 == 0x43) {
        if (0.0 <= *(double *)((int)fVar17 + 0x48)) {
          pMVar11 = Build_Pitch_Matrix(&local_214,
                                       (local_14 * local_18 + local_20 * local_c +
                                       *(float *)((int)fVar17 + 0x3c)) * param_1 * ___real_40400000)
          ;
          pMVar14 = &local_f4;
          for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
            pMVar14->right_x = pMVar11->right_x;
            pMVar11 = (MAT_3D *)&pMVar11->right_y;
            pMVar14 = (MAT_3D *)&pMVar14->right_y;
          }
          pMVar14 = (MAT_3D *)((int)local_8 + 0x20);
          pMVar11 = &local_254;
        }
        else {
          pMVar11 = Build_Pitch_Matrix(&local_2d4,
                                       ((local_20 * local_c + *(float *)((int)fVar17 + 0x3c)) -
                                       local_14 * local_18) * param_1 * ___real_40400000);
          pMVar14 = &local_f4;
          for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
            pMVar14->right_x = pMVar11->right_x;
            pMVar11 = (MAT_3D *)&pMVar11->right_y;
            pMVar14 = (MAT_3D *)&pMVar14->right_y;
          }
          pMVar14 = (MAT_3D *)((int)local_8 + 0x20);
          pMVar11 = &local_314;
        }
        goto LAB_0049d268;
      }
      if (iVar10 == 0x44) {
        pMVar11 = Build_Roll_Matrix(&local_1b4,
                                    (-*(float *)((int)fVar17 + 0x24) - local_50 * local_18) *
                                    param_1 * ___real_40400000);
        pMVar14 = &local_f4;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar14->right_x = pMVar11->right_x;
          pMVar11 = (MAT_3D *)&pMVar11->right_y;
          pMVar14 = (MAT_3D *)&pMVar14->right_y;
        }
        pMVar14 = (MAT_3D *)((int)local_8 + 0x20);
        pMVar11 = &local_b4;
        goto LAB_0049d268;
      }
      if (iVar10 == 0x4b) {
        pfVar15 = local_174 + (int)local_10;
        local_10 = (float)((int)local_10 + 1);
        *pfVar15 = fVar17;
      }
      else if ((iVar10 == 0x4d) && (((byte)useD3D & 4) != 0)) {
        pfVar15 = afStack_1d4 + local_1c;
        local_1c = local_1c + 1;
        *pfVar15 = fVar17;
      }
    }
    fVar17 = *(float *)((int)local_8 + 0xa8);
    if (fVar17 == 0.0) {
      iVar10 = *(int *)((int)local_8 + 0xa4);
      while (iVar10 == 0) {
        local_8 = *(float *)((int)local_8 + 0xa0);
        if (local_8 == 0.0) {
          if (this->throttle <= ___real_3dcccccd) {
            return;
          }
          if ((*(uint *)(this->_padding_ + 0x14) & 0x600) != 0) {
            return;
          }
          iVar10 = UserPref_arcadeMode();
          if (iVar10 != 0) {
            return;
          }
          local_8 = 0.0;
          if (0 < (int)local_10) goto LAB_0049d2f7;
          goto LAB_0049d526;
        }
        iVar10 = *(int *)((int)local_8 + 0xa4);
      }
      fVar17 = *(float *)((int)local_8 + 0xa4);
    }
  } while( true );
LAB_0049d2f7:
  pMVar11 = obj_rel_parent_matrix(&local_134,(_OBJ76 *)local_174[(int)local_8],(_OBJ76 *)0x0);
  fVar17 = local_174[(int)local_8];
  pMVar14 = &local_b4;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar14->right_x = pMVar11->right_x;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
    pMVar14 = (MAT_3D *)&pMVar14->right_y;
  }
  if (0.0 <= *(double *)((int)fVar17 + 0x48)) {
    fVar17 = Get_TimeLocal();
    fVar17 = fVar17 * ___real_c0a00000;
  }
  else {
    fVar17 = Get_TimeLocal();
    fVar17 = fVar17 * DUST_SCATTER_FLY;
  }
  pMVar11 = Build_Roll_Matrix(&local_134,fVar17);
  pMVar14 = &local_f4;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar14->right_x = pMVar11->right_x;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
    pMVar14 = (MAT_3D *)&pMVar14->right_y;
  }
  pMVar11 = Matrix_Multiply(&local_134,&local_f4,&local_b4);
  p_Var12 = (_OBJ76 *)local_174[(int)local_8];
  pMVar14 = &local_b4;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar14->right_x = pMVar11->right_x;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
    pMVar14 = (MAT_3D *)&pMVar14->right_y;
  }
  p_Var12 = obj_get_parent(p_Var12);
  if ((p_Var12 == (_OBJ76 *)0x0) || (p_Var12->class_id != CLASS_ID_NACELLE_GEOMETRY)) {
    if (*(int *)(this->_padding_ + 0xd4) == 0) {
      local_c = 0.0;
      goto LAB_0049d3ce;
    }
    local_c = ___real_3e4ccccd;
LAB_0049d3e5:
    Rand_Counter = Rand_Counter + 1U & 0xff;
    EngineFlame::AddFlame
              (&engineFlame,&local_b4,
               (Pseudo_Rand_Number[Rand_Counter] * ___real_3dcccccd + ___real_3f800000) * local_c);
    if (engineSplash.splashTexture != 0) {
      local_74 = local_b4.posit_x;
      local_6c = (undefined1  [8])local_b4.posit_y;
      local_64 = local_b4.posit_z;
      local_44.x = local_b4.front_x;
      local_44.y = local_b4.front_y;
      local_44.z = local_b4.front_z;
      VVar5.y = local_b4.front_y;
      VVar5.x = local_b4.front_x;
      VVar5.z = local_b4.front_z;
      pVVar13 = ScaleVector(&local_38,local_c * ___real_41c80000,VVar5);
      local_2c.x = pVVar13->x;
      local_2c.y = pVVar13->y;
      local_2c.z = pVVar13->z;
      local_14 = 1.0;
      VVar3.y._0_4_ = local_6c._0_4_;
      VVar3.x = local_74;
      VVar3.y._4_4_ = local_6c._4_4_;
      VVar3.z._0_4_ = SUB84(local_64,0);
      VVar3.z._4_4_ = (int)((ulonglong)local_64 >> 0x20);
      iVar10 = Terrain_GetIntersection(VVar3,*pVVar13,&local_14,&local_5c);
      if (iVar10 != 0) {
        pMVar11 = Build_Orthogonal_Matrix(&local_134,(VECTOR_3D *)&local_134,unaff_ESI);
        fVar8 = local_14;
        fVar17 = local_2c.x * local_14;
        fVar1 = (float)local_74;
        pMVar14 = &local_1b4;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar14->right_x = pMVar11->right_x;
          pMVar11 = (MAT_3D *)&pMVar11->right_y;
          pMVar14 = (MAT_3D *)&pMVar14->right_y;
        }
        local_1b4.posit_x = (double)(fVar17 + fVar1);
        local_1b4.posit_y = (double)(local_2c.y * fVar8 + (float)(double)local_6c);
        local_1b4.posit_z = (double)(local_2c.z * fVar8 + (float)local_64);
        EngineSplash::AddSplash(&engineSplash,&local_1b4,fVar8);
      }
    }
  }
  else {
    local_c = this->throttle * ___real_3e4ccccd;
LAB_0049d3ce:
    if (___real_3c23d70a < local_c) goto LAB_0049d3e5;
  }
  local_8 = (float)((int)local_8 + 1);
  if ((int)local_10 <= (int)local_8) {
LAB_0049d526:
    if ((0 < local_1c) && (this->airBorne < ___real_3f4ccccd)) {
      local_14 = this->airBorne * ___real_3fa00000;
      local_18 = (1.0 - local_14) * this->throttle;
      fVar17 = local_18 * param_1 + this->dustTimer;
      this->dustTimer = fVar17;
      uVar16 = (ushort)(0.0 < fVar17) << 8 | (ushort)NAN(fVar17) << 10;
      while ((POPCOUNT((char)(uVar16 >> 8)) & 1U) != 0) {
        VVar7.x = (float)this->_padding_;
        VVar7.y = (float)this->_padding_;
        VVar7.z = (float)this->_padding_;
        pMVar11 = Spinner(&local_134,(MAT_3D *)(this->_padding_ + 0x20),VVar7,-this->dustTimer);
        iVar2 = local_1c;
        fVar17 = (float)this->_padding_;
        param_1 = 0.0;
        fVar1 = this->dustTimer;
        pMVar14 = &local_b4;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar14->right_x = pMVar11->right_x;
          pMVar11 = (MAT_3D *)&pMVar11->right_y;
          pMVar14 = (MAT_3D *)&pMVar14->right_y;
        }
        local_b4.posit_x = (double)((float)local_b4.posit_x - fVar17 * fVar1);
        local_b4.posit_y =
             (double)((float)local_b4.posit_y - this->dustTimer * (float)this->_padding_);
        local_b4.posit_z =
             (double)((float)local_b4.posit_z - (float)this->_padding_ * this->dustTimer);
        if (0 < iVar2) {
          local_20 = local_14 * ___real_40400000 + ___real_40000000;
          local_c = local_18 * local_18 * ___real_40000000;
          do {
            pMVar11 = obj_rel_parent_matrix
                                (&local_134,(_OBJ76 *)afStack_1d4[(int)param_1],
                                 (_OBJ76 *)this->_padding_);
            pfVar15 = local_174;
            for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
              *pfVar15 = pMVar11->right_x;
              pMVar11 = (MAT_3D *)&pMVar11->right_y;
              pfVar15 = pfVar15 + 1;
            }
            local_5c.x = (float)local_14c;
            local_5c.y = (float)local_144;
            local_5c.z = (float)local_13c;
            local_38.x = local_5c.x;
            local_38.y = local_5c.y;
            local_38.z = local_5c.z;
            Vector_Transform(&local_38,&local_38,1,&local_b4);
            uVar9 = (Rand_Counter + 1U & 0xff) + 1;
            local_10 = *(float *)(&DAT_00c9021c + uVar9 * 4);
            Rand_Counter = uVar9 & 0xff;
            local_8 = Pseudo_Rand_Number[Rand_Counter];
            local_38.x = local_20 * local_10 + local_38.x;
            local_38.z = local_20 * local_8 + local_38.z;
            Terrain_GetHeightAndNormal((double)local_38.x,(double)local_38.z,&local_38.y,&local_44);
            local_2c.x = local_c * local_10 + (float)this->_padding_ * ___real_3e800000;
            local_2c.y = 0.0;
            local_2c.z = local_c * local_8 + (float)this->_padding_ * ___real_3e800000;
            VVar4.y = 0.0;
            VVar4.x = local_2c.x;
            VVar4.z = local_2c.z;
            VVar6.y = local_44.y;
            VVar6.x = local_44.x;
            VVar6.z = local_44.z;
            pVVar13 = AddMultVectors((VECTOR_3D *)(local_6c + 4),VVar4,
                                     -(local_44.x * local_2c.x + local_44.z * local_2c.z +
                                      local_44.y * 0.0),VVar6);
            local_2c.x = pVVar13->x;
            local_2c.y = pVVar13->y;
            local_2c.z = pVVar13->z;
            DustEffect::AddDust(&dustEffect,&local_38,&local_2c,this->dustTimer);
            param_1 = (float)((int)param_1 + 1);
          } while ((int)param_1 < local_1c);
        }
        this->dustTimer = this->dustTimer - DUST_PAUSE;
        uVar16 = (ushort)(0.0 < this->dustTimer) << 8 | (ushort)NAN(this->dustTimer) << 10;
      }
    }
    return;
  }
  goto LAB_0049d2f7;
}


