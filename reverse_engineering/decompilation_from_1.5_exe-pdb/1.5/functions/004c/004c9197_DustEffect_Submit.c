/*
 * Entry: 004c9197
 * Name: DustEffect::Submit
 * Namespace: DustEffect
 * Signature: void Submit(DustEffect * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

void __thiscall DustEffect::Submit(DustEffect *this,CAMERA *param_1)

{
  POLYGON_SKIN *pPVar1;
  POLYGON_SKIN PVar2;
  POLYGON_SKIN PVar3;
  float fVar4;
  float fVar5;
  _ZSORTING *p_Var6;
  double *pdVar7;
  int iVar8;
  float *pfVar9;
  DustPuff *pDVar10;
  float *pfVar11;
  POLYGON_SKIN *pPVar12;
  int unaff_EDI;
  bool bVar13;
  double adStack_28154 [320];
  float afStack_27754 [40384];
  double local_54;
  undefined8 local_4c;
  int local_44;
  float local_40;
  float local_38;
  float local_34;
  DustEffect *local_30;
  SPHERE local_2c;
  undefined1 local_1c [12];
  _ZSORTING *p_Stack_10;
  DustPuff *local_c;
  float *local_8;
  
  local_8 = (float *)0x0;
  local_40 = (float)(param_1->bSphere_Center).x;
  local_38 = (float)(param_1->bSphere_Center).z;
  local_34 = (float)param_1->bSphere_Radius;
  local_30 = this;
  local_44 = Set_Rounding(unaff_EDI);
  if (((byte)useD3D & 4) == 0) {
    pdVar7 = adStack_28154;
    local_4c = (double)CONCAT44(64.0 / (param_1->Zoom_Factor * param_1->Max_Depth),(long)local_4c);
    do {
      *(double **)(pdVar7 + 0x140) = pdVar7;
      pdVar7 = (double *)((int)pdVar7 + 0xa04);
    } while (pdVar7 < &local_54);
    local_c = this->puffFirst;
    bVar13 = local_c < this->puffLast;
    while (bVar13) {
      local_2c.radius = local_c->radius;
      local_2c.origin.x = (local_c->pos).x;
      local_2c.origin.y = (local_c->pos).y;
      local_2c.origin.z = (local_c->pos).z;
      if ((ABS(local_2c.origin.x - local_40) <= local_2c.radius + local_34) &&
         (ABS(local_2c.origin.z - local_38) <= local_2c.radius + local_34)) {
        Vector_Transform(&local_2c.origin,&local_2c.origin,1,&param_1->Matrix);
        pDVar10 = local_c;
        if (local_2c.origin.z <= local_2c.radius + local_2c.radius) {
          if (local_8 != (float *)0x0) goto LAB_004c9453;
          local_8 = (float *)0x1;
        }
        local_2c.origin.y = local_c->radius + local_2c.origin.y;
        bVar13 = Is_Sphere_Visible(param_1,&local_2c);
        if (bVar13) {
          local_54 = (double)(local_2c.origin.z * local_4c._4_4_ + (float)Float2Int);
          iVar8 = local_54._0_4_;
          if (0x3f < local_54._0_4_) {
            Trace("DustEffect clamped dist\n");
            iVar8 = 0x3f;
          }
          pfVar9 = afStack_27754 + iVar8 * 0x281;
          pfVar11 = (float *)*pfVar9;
          if (pfVar11 < pfVar9) {
            fVar4 = pDVar10->frame;
            fVar5 = (float)Float2Int;
            *pfVar9 = (float)(pfVar11 + 5);
            *pfVar11 = local_2c.origin.x;
            unique0x0000aa00 = (double)(fVar4 + fVar5);
            pfVar11[1] = local_2c.origin.y;
            pfVar11[2] = local_2c.origin.z;
            pfVar11[3] = local_2c.radius;
            pfVar11[4] = (float)local_1c._8_4_;
          }
        }
      }
LAB_004c9453:
      local_c = local_c + 1;
      bVar13 = local_c < local_30->puffLast;
    }
    local_c = (DustPuff *)0x0;
    pfVar11 = afStack_27754;
    do {
      local_8 = pfVar11;
      if (pfVar11 + -0x280 < (float *)*pfVar11) {
        pPVar12 = (POLYGON_SKIN *)(pfVar11 + -0x27e);
        do {
          p_Var6 = SortingTableCurrent;
          SortingTableCurrent->vcnt = 0;
          p_Var6->Type = 9;
          p_Var6->Skin_Color = pPVar12[2];
          p_Var6->Bitmap_Operation = 0x50004;
          fVar4 = 1.0 / (float)*pPVar12;
          p_Var6[1].vcnt = (long)((float)pPVar12[-2] * fVar4 * param_1->Const_x + param_1->Orig_x);
          p_Var6[1].Skin_Color =
               (POLYGON_SKIN)((float)pPVar12[-1] * param_1->Const_y * fVar4 + param_1->Orig_y);
          p_Var6[1].Bitmap_Operation = (long)*pPVar12;
          fVar5 = (float)pPVar12[1] * fVar4 * param_1->Const_x;
          p_Var6[1].Type = (long)(fVar5 + fVar5);
          p_Var6[1].Z_Value = (float)pPVar12[1] * param_1->Const_y * fVar4 * -2.0;
          p_Var6[1].Previous = (_ZSORTING *)pPVar12[-2];
          *(POLYGON_SKIN *)(p_Var6 + 2) = pPVar12[-1];
          p_Var6[2].Skin_Color = *pPVar12;
          p_Var6[1].Next = (_ZSORTING *)pPVar12[1];
          PVar2 = *pPVar12;
          PVar3 = pPVar12[1];
          p_Var6->Z_Value = (float)PVar2 - (float)PVar3;
          ZSORTAdd((float)PVar2 - (float)PVar3);
          local_c = (DustPuff *)((int)local_c + 1);
          pPVar1 = pPVar12 + 3;
          pPVar12 = pPVar12 + 5;
        } while (pPVar1 < (POLYGON_SKIN *)*local_8);
      }
    } while (((int)local_c < 100) &&
            (pfVar11 = local_8 + 0x281, pdVar7 = (double *)(local_8 + 1), local_8 = pfVar11,
            pdVar7 < &local_54));
  }
  else {
    pDVar10 = this->puffFirst;
    bVar13 = pDVar10 < this->puffLast;
    while (bVar13) {
      local_1c._0_4_ = (pDVar10->pos).x;
      local_1c._4_4_ = (pDVar10->pos).y;
      fVar4 = (pDVar10->pos).z;
      stack0xffffffec = (double)CONCAT44(pDVar10->radius,fVar4);
      fVar5 = pDVar10->radius + local_34;
      if ((ABS((float)local_1c._0_4_ - local_40) <= fVar5) && (ABS(fVar4 - local_38) <= fVar5)) {
        Vector_Transform((VECTOR_3D *)local_1c,(VECTOR_3D *)local_1c,1,&param_1->Matrix);
        if ((float)local_1c._8_4_ <= (float)p_Stack_10 + (float)p_Stack_10) {
          if (local_8 != (float *)0x0) goto LAB_004c9318;
          local_8 = (float *)0x1;
        }
        local_1c._4_4_ = (float)local_1c._4_4_ + pDVar10->radius;
        bVar13 = Is_Sphere_Visible(param_1,(SPHERE *)local_1c);
        p_Var6 = SortingTableCurrent;
        if (bVar13) {
          fVar4 = pDVar10->frame;
          fVar5 = (float)Float2Int;
          SortingTableCurrent->vcnt = 0;
          p_Var6->Type = 9;
          p_Var6->Bitmap_Operation = 0x50004;
          local_4c = (double)(fVar4 + fVar5);
          (p_Var6->Skin_Color).Color = (long)local_4c;
          fVar4 = 1.0 / (float)local_1c._8_4_;
          p_Var6[1].vcnt =
               (long)((float)local_1c._0_4_ * fVar4 * param_1->Const_x + param_1->Orig_x);
          p_Var6[1].Skin_Color =
               (POLYGON_SKIN)(param_1->Const_y * fVar4 * (float)local_1c._4_4_ + param_1->Orig_y);
          p_Var6[1].Bitmap_Operation = local_1c._8_4_;
          fVar5 = (float)p_Stack_10 * fVar4 * param_1->Const_x;
          p_Var6[1].Type = (long)(fVar5 + fVar5);
          p_Var6[1].Z_Value = fVar4 * param_1->Const_y * (float)p_Stack_10 * -2.0;
          p_Var6[1].Previous = (_ZSORTING *)local_1c._0_4_;
          p_Var6[2].vcnt = local_1c._4_4_;
          p_Var6[2].Skin_Color.Color = local_1c._8_4_;
          p_Var6[1].Next = p_Stack_10;
          p_Var6->Z_Value = (float)local_1c._8_4_ - (float)p_Stack_10;
          ZSORTAdd((float)local_1c._8_4_ - (float)p_Stack_10);
        }
      }
LAB_004c9318:
      pDVar10 = pDVar10 + 1;
      bVar13 = pDVar10 < local_30->puffLast;
    }
  }
  Set_Rounding(unaff_EDI);
  return;
}
