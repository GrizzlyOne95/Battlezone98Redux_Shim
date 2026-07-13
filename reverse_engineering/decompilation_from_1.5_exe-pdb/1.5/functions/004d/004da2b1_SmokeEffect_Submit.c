/*
 * Entry: 004da2b1
 * Name: SmokeEffect::Submit
 * Namespace: SmokeEffect
 * Signature: void Submit(SmokeEffect * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

void __thiscall SmokeEffect::Submit(SmokeEffect *this,CAMERA *param_1)

{
  POLYGON_SKIN *pPVar1;
  int *piVar2;
  POLYGON_SKIN PVar3;
  POLYGON_SKIN PVar4;
  float fVar5;
  float *pfVar6;
  float fVar7;
  _ZSORTING *p_Var8;
  double *pdVar9;
  int iVar10;
  float *pfVar11;
  SmokePuff *pSVar12;
  SmokeEffect *pSVar13;
  POLYGON_SKIN *pPVar14;
  int unaff_EDI;
  bool bVar15;
  double adStack_28150 [320];
  SmokeEffect SStack_27750;
  double local_50;
  undefined8 local_48;
  int local_40;
  float local_3c;
  float local_34;
  float local_30;
  SPHERE local_2c;
  undefined1 local_1c [12];
  _ZSORTING *p_Stack_10;
  SmokeEffect *local_c;
  SmokePuff *local_8;
  
  local_8 = (SmokePuff *)0x4da2be;
  local_3c = (float)(param_1->bSphere_Center).x;
  local_34 = (float)(param_1->bSphere_Center).z;
  local_30 = (float)param_1->bSphere_Radius;
  local_c = this;
  local_40 = Set_Rounding(unaff_EDI);
  if (((byte)useD3D & 4) == 0) {
    pdVar9 = adStack_28150;
    local_48 = (double)CONCAT44(64.0 / (param_1->Zoom_Factor * param_1->Max_Depth),(long)local_48);
    do {
      *(double **)(pdVar9 + 0x140) = pdVar9;
      pdVar9 = (double *)((int)pdVar9 + 0xa04);
    } while (pdVar9 < &local_50);
    local_8 = this->puffFirst;
    bVar15 = local_8 < this->puffLast;
    while (bVar15) {
      local_2c.radius = local_8->radius;
      local_2c.origin.x = (local_8->pos).x;
      local_2c.origin.y = (local_8->pos).y;
      local_2c.origin.z = (local_8->pos).z;
      if ((ABS(local_2c.origin.x - local_3c) <= local_2c.radius + local_30) &&
         (ABS(local_2c.origin.z - local_34) <= local_2c.radius + local_30)) {
        Vector_Transform(&local_2c.origin,&local_2c.origin,1,&param_1->Matrix);
        bVar15 = Is_Sphere_Visible(param_1,&local_2c);
        if (bVar15) {
          local_50 = (double)(local_2c.origin.z * local_48._4_4_ + (float)Float2Int);
          iVar10 = local_50._0_4_;
          if (0x3f < local_50._0_4_) {
            Trace("SmokeEffect clamped dist\n");
            iVar10 = 0x3f;
          }
          pfVar11 = (float *)((int)SStack_27750.emitterFirst + iVar10 * 0xa04 + -0x28);
          pfVar6 = (float *)*pfVar11;
          if (pfVar6 < pfVar11) {
            *pfVar11 = (float)(pfVar6 + 5);
            fVar5 = local_8->frame;
            fVar7 = (float)Float2Int;
            *pfVar6 = local_2c.origin.x;
            pfVar6[1] = local_2c.origin.y;
            unique0x0000aa00 = (double)(fVar5 + fVar7);
            pfVar6[2] = local_2c.origin.z;
            pfVar6[3] = local_2c.radius;
            pfVar6[4] = (float)local_1c._8_4_;
          }
        }
      }
      local_8 = local_8 + 1;
      bVar15 = local_8 < local_c->puffLast;
    }
    local_8 = (SmokePuff *)0x0;
    pSVar13 = &SStack_27750;
    do {
      local_c = pSVar13;
      if (&pSVar13[-1].puffFirst[0x7c6].frame < (undefined1 *)pSVar13->_padding_) {
        pPVar14 = (POLYGON_SKIN *)&pSVar13[-1].puffFirst[0x7c6].rate;
        do {
          p_Var8 = SortingTableCurrent;
          SortingTableCurrent->vcnt = 0;
          p_Var8->Type = 9;
          p_Var8->Skin_Color = pPVar14[2];
          p_Var8->Bitmap_Operation = 0x50004;
          fVar5 = 1.0 / (float)*pPVar14;
          p_Var8[1].vcnt = (long)(fVar5 * param_1->Const_x * (float)pPVar14[-2] + param_1->Orig_x);
          p_Var8[1].Skin_Color =
               (POLYGON_SKIN)(param_1->Const_y * fVar5 * (float)pPVar14[-1] + param_1->Orig_y);
          p_Var8[1].Bitmap_Operation = (long)*pPVar14;
          fVar7 = (float)pPVar14[1] * fVar5 * param_1->Const_x;
          p_Var8[1].Type = (long)(fVar7 + fVar7);
          p_Var8[1].Z_Value = (float)pPVar14[1] * param_1->Const_y * fVar5 * -2.0;
          p_Var8[1].Previous = (_ZSORTING *)pPVar14[-2];
          *(POLYGON_SKIN *)(p_Var8 + 2) = pPVar14[-1];
          p_Var8[2].Skin_Color = *pPVar14;
          p_Var8[1].Next = (_ZSORTING *)pPVar14[1];
          PVar3 = *pPVar14;
          PVar4 = pPVar14[1];
          p_Var8->Z_Value = (float)PVar3 - (float)PVar4;
          ZSORTAdd((float)PVar3 - (float)PVar4);
          local_8 = (SmokePuff *)((int)local_8 + 1);
          pPVar1 = pPVar14 + 3;
          pPVar14 = pPVar14 + 5;
        } while (pPVar1 < (POLYGON_SKIN *)local_c->_padding_);
      }
    } while (((int)local_8 < 100) &&
            (pSVar13 = (SmokeEffect *)&local_c->emitterFirst[0x7e].frames,
            piVar2 = &local_c->_padding_, local_c = pSVar13, piVar2 < &local_50));
  }
  else {
    pSVar12 = this->puffFirst;
    bVar15 = pSVar12 < this->puffLast;
    while (bVar15) {
      local_1c._0_4_ = (pSVar12->pos).x;
      local_1c._4_4_ = (pSVar12->pos).y;
      fVar5 = (pSVar12->pos).z;
      stack0xffffffec = (double)CONCAT44(pSVar12->radius,fVar5);
      fVar7 = pSVar12->radius + local_30;
      if ((ABS((float)local_1c._0_4_ - local_3c) <= fVar7) && (ABS(fVar5 - local_34) <= fVar7)) {
        Vector_Transform((VECTOR_3D *)local_1c,(VECTOR_3D *)local_1c,1,&param_1->Matrix);
        bVar15 = Is_Sphere_Visible(param_1,(SPHERE *)local_1c);
        p_Var8 = SortingTableCurrent;
        if (bVar15) {
          fVar5 = pSVar12->frame;
          fVar7 = (float)Float2Int;
          SortingTableCurrent->vcnt = 0;
          p_Var8->Type = 9;
          p_Var8->Bitmap_Operation = 0x50004;
          local_48 = (double)(fVar5 + fVar7);
          (p_Var8->Skin_Color).Color = (long)local_48;
          fVar5 = 1.0 / (float)local_1c._8_4_;
          p_Var8[1].vcnt =
               (long)((float)local_1c._0_4_ * fVar5 * param_1->Const_x + param_1->Orig_x);
          p_Var8[1].Skin_Color =
               (POLYGON_SKIN)(param_1->Const_y * (float)local_1c._4_4_ * fVar5 + param_1->Orig_y);
          p_Var8[1].Bitmap_Operation = local_1c._8_4_;
          fVar7 = (float)p_Stack_10 * fVar5 * param_1->Const_x;
          p_Var8[1].Type = (long)(fVar7 + fVar7);
          p_Var8[1].Z_Value = fVar5 * param_1->Const_y * (float)p_Stack_10 * -2.0;
          p_Var8[1].Previous = (_ZSORTING *)local_1c._0_4_;
          p_Var8[2].vcnt = local_1c._4_4_;
          p_Var8[2].Skin_Color.Color = local_1c._8_4_;
          p_Var8[1].Next = p_Stack_10;
          p_Var8->Z_Value = (float)local_1c._8_4_ - (float)p_Stack_10;
          ZSORTAdd((float)local_1c._8_4_ - (float)p_Stack_10);
        }
      }
      pSVar12 = pSVar12 + 1;
      bVar15 = pSVar12 < local_c->puffLast;
    }
  }
  Set_Rounding(unaff_EDI);
  return;
}
