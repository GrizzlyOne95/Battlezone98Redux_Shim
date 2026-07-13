/*
 * Entry: 004d89d3
 * Name: Reticle::Submit
 * Namespace: Reticle
 * Signature: void Submit(Reticle * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::Submit(Reticle *this,CAMERA *param_1)

{
  double dVar1;
  POLYGON_SKIN *pPVar2;
  POLYGON_SKIN PVar3;
  _ZSORTING *p_Var4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  VECTOR_3D VVar10;
  VECTOR_3D VVar11;
  VECTOR_3D VVar12;
  VECTOR_3D VVar13;
  _ZSORTING *p_Var14;
  MAT_3D *pMVar15;
  VECTOR_3D *pVVar16;
  int iVar17;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  MAT_3D local_1b8;
  MAT_3D local_178;
  VECTOR_3D local_138;
  VECTOR_3D local_12c;
  VECTOR_3D local_120;
  VECTOR_3D local_114;
  VECTOR_3D local_108;
  MAT_3D local_fc;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  VECTOR_3D local_8c;
  float local_80;
  float local_7c;
  float local_78;
  MAT_3D local_74;
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  if (((((View_Record.Current_View == COCKPIT_VIEW) || (View_Record.Current_View == BINOCULAR_VIEW))
       || (View_Record.Current_View == FIX_EXTERN_VIEW)) || (View_Record.Current_View == CHASE_VIEW)
      ) && (param_1 == &View_Record.MainCam)) {
    if (View_Record.Intenal_View == 0) {
      pMVar15 = Matrix_Multiply(&local_178,&this->sightMat,&View_Record.MainCam.Matrix);
      pMVar18 = &local_74;
      for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
        pMVar18->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar18 = (MAT_3D *)&pMVar18->right_y;
      }
      local_20 = local_74.front_x * 12.0 + (float)local_74.posit_x;
      local_1c = local_74.front_y * 12.0 + (float)local_74.posit_y;
      local_18 = local_74.front_z * 12.0 + (float)local_74.posit_z;
      local_14 = local_74.right_x;
      local_10 = local_74.right_y;
      local_c = local_74.right_z;
      fVar19 = local_74.right_x;
      fVar20 = local_74.right_y;
      fVar21 = local_74.right_z;
      local_8 = GetSpriteWidth(this->reticleIndex);
      VVar5.y = fVar20;
      VVar5.x = fVar19;
      VVar5.z = fVar21;
      pVVar16 = ScaleVector(&local_8c,(float)local_8 * 0.02,VVar5);
      local_14 = local_74.up_x;
      local_30 = pVVar16->x;
      local_10 = local_74.up_y;
      local_2c = pVVar16->y;
      local_c = local_74.up_z;
      local_28 = pVVar16->z;
      fVar19 = local_74.up_x;
      fVar20 = local_74.up_y;
      fVar21 = local_74.up_z;
      local_8 = GetSpriteHeight(this->reticleIndex);
      VVar6.y = fVar20;
      VVar6.x = fVar19;
      VVar6.z = fVar21;
      pVVar16 = ScaleVector(&local_8c,(float)local_8 * 0.02,VVar6);
      p_Var4 = SortingTableCurrent;
      local_14 = pVVar16->x;
      local_10 = pVVar16->y;
      local_c = pVVar16->z;
      SortingTableCurrent->vcnt = 0;
      p_Var4->Type = 10;
      p_Var4->Bitmap_Operation = 4;
      p_Var4->Skin_Color = (POLYGON_SKIN)this->reticleIndex;
      p_Var4[1].vcnt = (long)((local_14 + local_20) - local_30);
      p_Var4[1].Skin_Color = (POLYGON_SKIN)((local_10 + local_1c) - local_2c);
      p_Var4[1].Bitmap_Operation = (long)((local_c + local_18) - local_28);
      p_Var4[1].Type = (long)(local_30 + local_14 + local_20);
      p_Var4[1].Z_Value = local_2c + local_10 + local_1c;
      p_Var4[1].Next = (_ZSORTING *)(local_c + local_28 + local_18);
      p_Var4[1].Previous = (_ZSORTING *)((local_20 - local_14) + local_30);
      p_Var4[2].vcnt = (long)((local_1c - local_10) + local_2c);
      p_Var4[2].Skin_Color = (POLYGON_SKIN)((local_18 - local_c) + local_28);
      p_Var4[2].Bitmap_Operation = (long)((local_20 - local_14) - local_30);
      p_Var4[2].Type = (long)((local_1c - local_10) - local_2c);
      p_Var4[2].Z_Value = (local_18 - local_c) - local_28;
      fVar19 = VectGetMin((VECTOR_3D *)(p_Var4 + 1),4);
      p_Var4->Z_Value = fVar19;
      ZSORTAdd(fVar19);
      iVar17 = 0;
      do {
        p_Var14 = SortingTableCurrent;
        iVar17 = iVar17 + 1;
        SortingTableCurrent->vcnt = 0;
        p_Var14->Type = 9;
        p_Var14->Skin_Color = (POLYGON_SKIN)this->dotIndex;
        fVar19 = 12.0 - ((float)iVar17 + (float)iVar17);
        p_Var14->Bitmap_Operation = 0x50004;
        p_Var4 = (_ZSORTING *)(local_74.front_x * fVar19 + (float)local_74.posit_x);
        fVar20 = fVar19 * local_74.front_y + (float)local_74.posit_y;
        PVar3 = (POLYGON_SKIN)(fVar19 * local_74.front_z + (float)local_74.posit_z);
        fVar19 = 1.0 / (float)PVar3;
        p_Var14[1].vcnt =
             (long)(fVar19 * (float)p_Var4 * View_Record.MainCam.Const_x +
                   View_Record.MainCam.Orig_x);
        p_Var14[1].Skin_Color =
             (POLYGON_SKIN)
             (View_Record.MainCam.Const_y * fVar19 * fVar20 + View_Record.MainCam.Orig_y);
        p_Var14[1].Bitmap_Operation = (long)PVar3;
        p_Var14[1].Type = (long)(fVar19 * View_Record.MainCam.Const_x * 0.2);
        p_Var14[1].Z_Value = View_Record.MainCam.Const_y * fVar19 * -0.2;
        p_Var14[1].Previous = p_Var4;
        p_Var14[2].vcnt = (long)fVar20;
        p_Var14[2].Skin_Color = PVar3;
        p_Var14[1].Next = (_ZSORTING *)0x3dcccccd;
        p_Var14->Z_Value = (float)PVar3;
        local_8 = iVar17;
        ZSORTAdd((float)PVar3);
      } while (iVar17 < 3);
      pMVar15 = Matrix_Multiply(&local_178,&this->horizMat,&View_Record.MainCam.Matrix);
      pMVar18 = &local_fc;
      for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
        pMVar18->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar18 = (MAT_3D *)&pMVar18->right_y;
      }
      local_20 = local_fc.front_x * 12.0 + (float)local_fc.posit_x;
      local_1c = local_fc.front_y * 12.0 + (float)local_fc.posit_y;
      local_18 = local_fc.front_z * 12.0 + (float)local_fc.posit_z;
      local_14 = local_fc.right_x;
      local_10 = local_fc.right_y;
      local_c = local_fc.right_z;
      local_8 = GetSpriteWidth(this->horizonIndex);
      VVar7.y = local_fc.right_y;
      VVar7.x = local_fc.right_x;
      VVar7.z = local_fc.right_z;
      pVVar16 = ScaleVector(&local_8c,(float)local_8 * 0.02,VVar7);
      local_14 = local_fc.up_x;
      local_30 = pVVar16->x;
      local_10 = local_fc.up_y;
      local_2c = pVVar16->y;
      local_c = local_fc.up_z;
      local_28 = pVVar16->z;
      local_8 = GetSpriteHeight(this->horizonIndex);
      VVar8.y = local_fc.up_y;
      VVar8.x = local_fc.up_x;
      VVar8.z = local_fc.up_z;
      pVVar16 = ScaleVector(&local_8c,(float)local_8 * 0.02,VVar8);
      p_Var4 = SortingTableCurrent;
      local_14 = pVVar16->x;
      local_10 = pVVar16->y;
      local_c = pVVar16->z;
      SortingTableCurrent->vcnt = 0;
      p_Var4->Type = 10;
      p_Var4->Bitmap_Operation = 4;
      p_Var4->Skin_Color = (POLYGON_SKIN)this->horizonIndex;
      p_Var4[1].vcnt = (long)((local_14 + local_20) - local_30);
      p_Var4[1].Skin_Color = (POLYGON_SKIN)((local_10 + local_1c) - local_2c);
      p_Var4[1].Bitmap_Operation = (long)((local_c + local_18) - local_28);
      p_Var4[1].Type = (long)(local_30 + local_14 + local_20);
      p_Var4[1].Z_Value = local_2c + local_10 + local_1c;
      p_Var4[1].Next = (_ZSORTING *)(local_c + local_28 + local_18);
      p_Var4[1].Previous = (_ZSORTING *)((local_20 - local_14) + local_30);
      p_Var4[2].vcnt = (long)((local_1c - local_10) + local_2c);
      p_Var4[2].Skin_Color = (POLYGON_SKIN)((local_18 - local_c) + local_28);
      p_Var4[2].Bitmap_Operation = (long)((local_20 - local_14) - local_30);
      p_Var4[2].Type = (long)((local_1c - local_10) - local_2c);
      p_Var4[2].Z_Value = (local_18 - local_c) - local_28;
      fVar19 = VectGetMin((VECTOR_3D *)(p_Var4 + 1),4);
      p_Var4->Z_Value = fVar19;
      ZSORTAdd(fVar19);
      if (this->ladderIndex != 0) {
        local_34 = -0x1e;
        do {
          pMVar15 = Build_Pitch_Matrix(&local_1b8,(float)local_34 * 0.017453292);
          pMVar18 = &local_178;
          for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
            pMVar18->right_x = pMVar15->right_x;
            pMVar15 = (MAT_3D *)&pMVar15->right_y;
            pMVar18 = (MAT_3D *)&pMVar18->right_y;
          }
          pMVar15 = Matrix_Multiply(&local_1b8,&local_178,&local_fc);
          pMVar18 = &local_74;
          for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
            pMVar18->right_x = pMVar15->right_x;
            pMVar15 = (MAT_3D *)&pMVar15->right_y;
            pMVar18 = (MAT_3D *)&pMVar18->right_y;
          }
          local_80 = local_74.front_x * 12.0 + (float)local_74.posit_x;
          local_7c = local_74.front_y * 12.0 + (float)local_74.posit_y;
          local_78 = local_74.front_z * 12.0 + (float)local_74.posit_z;
          local_a4 = local_74.right_x;
          local_a0 = local_74.right_y;
          local_9c = local_74.right_z;
          VVar9.y = local_74.right_y;
          VVar9.x = local_74.right_x;
          VVar9.z = local_74.right_z;
          pVVar16 = ScaleVector(&local_120,0.79999995,VVar9);
          local_8 = this->ladderIndex;
          local_20 = pVVar16->x;
          local_1c = pVVar16->y;
          local_18 = pVVar16->z;
          if (local_34 != 0) {
            local_8 = local_8 + 2;
          }
          local_bc = local_74.right_x;
          local_b8 = local_74.right_y;
          local_b4 = local_74.right_z;
          fVar19 = local_74.right_x;
          fVar20 = local_74.right_y;
          fVar21 = local_74.right_z;
          local_24 = GetSpriteWidth(local_8);
          local_24 = local_24 * 2;
          VVar10.y = fVar20;
          VVar10.x = fVar19;
          VVar10.z = fVar21;
          pVVar16 = ScaleVector(&local_12c,(float)local_24 * 0.02,VVar10);
          local_b0 = local_74.up_x;
          local_14 = pVVar16->x;
          local_ac = local_74.up_y;
          local_10 = pVVar16->y;
          local_a8 = local_74.up_z;
          local_c = pVVar16->z;
          fVar19 = local_74.up_x;
          fVar20 = local_74.up_y;
          fVar21 = local_74.up_z;
          local_24 = GetSpriteHeight(local_8);
          VVar11.y = fVar20;
          VVar11.x = fVar19;
          VVar11.z = fVar21;
          pVVar16 = ScaleVector(&local_138,(float)local_24 * 0.02,VVar11);
          iVar17 = local_8;
          p_Var4 = SortingTableCurrent;
          local_30 = pVVar16->x;
          local_2c = pVVar16->y;
          local_28 = pVVar16->z;
          SortingTableCurrent->vcnt = 0;
          fVar19 = (local_30 + local_80) - local_20;
          p_Var4->Type = 10;
          (p_Var4->Skin_Color).Color = local_8;
          p_Var4->Bitmap_Operation = 4;
          p_Var4[1].vcnt = (long)fVar19;
          PVar3 = (POLYGON_SKIN)((local_2c + local_7c) - local_1c);
          p_Var4[1].Skin_Color = PVar3;
          fVar20 = (local_28 + local_78) - local_18;
          p_Var4[1].Bitmap_Operation = (long)fVar20;
          p_Var4[1].Type = (long)(fVar19 + local_14);
          p_Var4[1].Z_Value = (float)PVar3 + local_10;
          p_Var4[1].Next = (_ZSORTING *)(fVar20 + local_c);
          fVar19 = (local_80 - local_30) - local_20;
          p_Var4[1].Previous = (_ZSORTING *)(local_14 + fVar19);
          fVar20 = (local_7c - local_2c) - local_1c;
          p_Var4[2].vcnt = (long)(local_10 + fVar20);
          fVar21 = (local_78 - local_28) - local_18;
          p_Var4[2].Skin_Color = (POLYGON_SKIN)(local_c + fVar21);
          p_Var4[2].Bitmap_Operation = (long)fVar19;
          p_Var4[2].Type = (long)fVar20;
          p_Var4[2].Z_Value = fVar21;
          fVar19 = VectGetMin((VECTOR_3D *)(p_Var4 + 1),4);
          p_Var4->Z_Value = fVar19;
          ZSORTAdd(fVar19);
          local_8 = iVar17 + 1;
          local_98 = local_74.right_x;
          local_94 = local_74.right_y;
          local_90 = local_74.right_z;
          fVar19 = local_74.right_x;
          fVar20 = local_74.right_y;
          fVar21 = local_74.right_z;
          local_24 = GetSpriteWidth(local_8);
          local_24 = local_24 * 2;
          VVar12.y = fVar20;
          VVar12.x = fVar19;
          VVar12.z = fVar21;
          pVVar16 = ScaleVector(&local_114,(float)local_24 * 0.02,VVar12);
          local_8c.x = local_74.up_x;
          local_14 = pVVar16->x;
          local_8c.y = local_74.up_y;
          local_10 = pVVar16->y;
          local_8c.z = local_74.up_z;
          local_c = pVVar16->z;
          fVar19 = local_74.up_x;
          fVar20 = local_74.up_y;
          fVar21 = local_74.up_z;
          local_24 = GetSpriteHeight(local_8);
          VVar13.y = fVar20;
          VVar13.x = fVar19;
          VVar13.z = fVar21;
          pVVar16 = ScaleVector(&local_108,(float)local_24 * 0.02,VVar13);
          p_Var14 = SortingTableCurrent;
          local_30 = pVVar16->x;
          local_2c = pVVar16->y;
          local_28 = pVVar16->z;
          fVar19 = local_20 + local_30 + local_80;
          SortingTableCurrent->vcnt = 0;
          (p_Var14->Skin_Color).Color = local_8;
          p_Var14->Type = 10;
          p_Var14->Bitmap_Operation = 4;
          p_Var14[1].vcnt = (long)(fVar19 - local_14);
          fVar20 = local_1c + local_2c + local_7c;
          p_Var14[1].Skin_Color = (POLYGON_SKIN)(fVar20 - local_10);
          p_Var4 = (_ZSORTING *)(local_18 + local_28 + local_78);
          p_Var14[1].Bitmap_Operation = (long)((float)p_Var4 - local_c);
          p_Var14[1].Type = (long)fVar19;
          p_Var14[1].Z_Value = fVar20;
          p_Var14[1].Next = p_Var4;
          p_Var4 = (_ZSORTING *)((local_80 - local_30) + local_20);
          p_Var14[1].Previous = p_Var4;
          fVar19 = (local_7c - local_2c) + local_1c;
          p_Var14[2].vcnt = (long)fVar19;
          PVar3 = (POLYGON_SKIN)((local_78 - local_28) + local_18);
          p_Var14[2].Skin_Color = PVar3;
          p_Var14[2].Bitmap_Operation = (long)((float)p_Var4 - local_14);
          p_Var14[2].Type = (long)(fVar19 - local_10);
          p_Var14[2].Z_Value = (float)PVar3 - local_c;
          fVar19 = VectGetMin((VECTOR_3D *)(p_Var14 + 1),4);
          p_Var14->Z_Value = fVar19;
          ZSORTAdd(fVar19);
          local_34 = local_34 + 5;
        } while (local_34 < 0x1f);
      }
    }
    if ((this->groundPos != (VECTOR_3D *)0x0) && (this->startCommand != CMD_NONE)) {
      local_98 = (this->sightMat).front_x;
      local_94 = (this->sightMat).front_y;
      local_90 = (this->sightMat).front_z;
      dVar1 = (double)this->groundPos->z;
      local_8c.x = local_98;
      local_8c.y = local_94;
      local_8c.z = local_90;
      pVVar16 = Terrain_GetNormal(&local_108,
                                  (double)CONCAT44(SUB84(dVar1,0),
                                                   (int)((ulonglong)(double)this->groundPos->x >>
                                                        0x20)),
                                  (double)CONCAT44(unaff_EDI,(int)((ulonglong)dVar1 >> 0x20)));
      local_8c.x = pVVar16->x;
      local_8c.y = pVVar16->y;
      local_8c.z = pVVar16->z;
      pMVar15 = Build_Orthogonal_Matrix(&local_1b8,unaff_EDI,unaff_ESI);
      pVVar16 = this->groundPos;
      pMVar18 = &local_74;
      for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
        pMVar18->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar18 = (MAT_3D *)&pMVar18->right_y;
      }
      local_74.posit_x = (double)pVVar16->x;
      local_74.posit_y = (double)pVVar16->y;
      local_74.posit_z = (double)pVVar16->z;
      pMVar15 = Matrix_Multiply(&local_1b8,&local_74,&View_Record.MainCam.Matrix);
      p_Var4 = SortingTableCurrent;
      pMVar18 = &local_74;
      for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
        pMVar18->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar18 = (MAT_3D *)&pMVar18->right_y;
      }
      if (((byte)D3IniFlags & 1) == 0) {
        SortingTableCurrent->vcnt = 0;
        p_Var4->Type = 10;
        p_Var4->Bitmap_Operation = 4;
        p_Var4->Skin_Color = (POLYGON_SKIN)this->groundIndex;
        p_Var4[1].vcnt = (long)(local_74.front_x * 3.0 + (float)local_74.posit_x);
        p_Var4[1].Skin_Color = (POLYGON_SKIN)(local_74.front_y * 3.0 + (float)local_74.posit_y);
        p_Var4[1].Bitmap_Operation = (long)(local_74.front_z * 3.0 + (float)local_74.posit_z);
        p_Var4[1].Type = (long)(local_74.right_x * 3.0 + (float)local_74.posit_x);
        p_Var4[1].Z_Value = local_74.right_y * 3.0 + (float)local_74.posit_y;
        p_Var4[1].Next = (_ZSORTING *)(local_74.right_z * 3.0 + (float)local_74.posit_z);
        p_Var4[1].Previous = (_ZSORTING *)((float)local_74.posit_x - local_74.front_x * 3.0);
        p_Var4[2].vcnt = (long)((float)local_74.posit_y - local_74.front_y * 3.0);
        p_Var4[2].Skin_Color = (POLYGON_SKIN)((float)local_74.posit_z - local_74.front_z * 3.0);
        p_Var4[2].Bitmap_Operation = (long)((float)local_74.posit_x - local_74.right_x * 3.0);
        p_Var4[2].Type = (long)((float)local_74.posit_y - local_74.right_y * 3.0);
        p_Var4[2].Z_Value = (float)local_74.posit_z - local_74.right_z * 3.0;
        fVar19 = VectGetMin((VECTOR_3D *)(p_Var4 + 1),4);
        p_Var4->Z_Value = fVar19;
      }
      else {
        SortingTableCurrent->vcnt = 0;
        p_Var4->Type = 1;
        p_Var4->Bitmap_Operation = 4;
        p_Var4->Skin_Color = (POLYGON_SKIN)this->groundIndex;
        pPVar2 = (POLYGON_SKIN *)this->groundPos;
        p_Var4[1].Skin_Color = *pPVar2;
        p_Var4[1].Bitmap_Operation = (long)pPVar2[1];
        p_Var4[1].Type = (long)pPVar2[2];
        p_Var4[1].vcnt = 0x40400000;
        fVar19 = (float)local_74.posit_z;
        p_Var4->Z_Value = fVar19;
      }
      ZSORTAdd(fVar19);
      p_Var4 = SortingTableCurrent;
      SortingTableCurrent->Bitmap_Operation = 0;
      p_Var4->Type = 8;
      p_Var4->vcnt = 2;
      (p_Var4->Skin_Color).Color = DisplayInterface::colorWhite;
      ((VECTOR_3D *)&p_Var4[1].vcnt)->x = (float)local_74.posit_x;
      p_Var4[1].Skin_Color = (POLYGON_SKIN)(float)local_74.posit_y;
      p_Var4[1].Bitmap_Operation = (long)(float)local_74.posit_z;
      p_Var4[1].Type = 0;
      p_Var4[1].Z_Value = 0.0;
      p_Var4[1].Next = (_ZSORTING *)TerrainIntensity;
      p_Var4[1].Previous = (_ZSORTING *)(local_74.up_x * 2.0 + (float)local_74.posit_x);
      p_Var4[2].vcnt = (long)(local_74.up_y * 2.0 + (float)local_74.posit_y);
      p_Var4[2].Skin_Color = (POLYGON_SKIN)(local_74.up_z * 2.0 + (float)local_74.posit_z);
      p_Var4[2].Bitmap_Operation = 0;
      p_Var4[2].Type = 0x3f800000;
      p_Var4[2].Z_Value = TerrainIntensity;
      fVar19 = GetMin((POINT_3D *)(p_Var4 + 1),2);
      p_Var4->Z_Value = fVar19;
      ZSORTAdd(fVar19);
    }
  }
  return;
}
