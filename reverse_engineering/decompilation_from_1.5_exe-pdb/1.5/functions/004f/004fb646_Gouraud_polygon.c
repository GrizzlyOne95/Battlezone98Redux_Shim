/*
 * Entry: 004fb646
 * Name: Gouraud_polygon
 * Namespace: Global
 * Signature: void Gouraud_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Gouraud_polygon(_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  undefined1 uVar11;
  uchar *puVar12;
  uint uVar13;
  uint uVar14;
  undefined1 uVar15;
  int iVar16;
  _GRAPHIC_BUFFER *p_Var17;
  POINT_3D *pPVar18;
  uint uVar19;
  ushort uVar20;
  uint uVar21;
  float *pfVar22;
  int iVar23;
  _GRAPHIC_BUFFER *p_Var24;
  uint *puVar25;
  uint *puVar26;
  int local_16c [31];
  int aiStack_f0 [33];
  double local_6c;
  double local_64;
  int local_5c;
  undefined8 local_58;
  int local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  int local_38;
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  _GRAPHIC_BUFFER *local_20;
  double local_1c;
  undefined8 local_14;
  double local_c;
  
  dVar2 = 100000.0;
  iVar23 = 0;
  iVar16 = 0;
  if (0 < param_3) {
    pfVar22 = &(param_2->Vector).y;
    do {
      fVar1 = pfVar22[4];
      local_16c[iVar16] = iVar16 + -1;
      aiStack_f0[iVar16 + 1] = iVar16 + 1;
      pfVar22[4] = (1.0 - fVar1) * LUM_SCALE * 256.0;
      if ((double)*pfVar22 < dVar2 != ((double)*pfVar22 == dVar2)) {
        dVar2 = (double)*pfVar22;
        iVar23 = iVar16;
      }
      iVar16 = iVar16 + 1;
      pfVar22 = pfVar22 + 6;
    } while (iVar16 < param_3);
  }
  aiStack_f0[iVar16] = 0;
  local_16c[0] = iVar16 + -1;
  local_5c = param_1->Width;
  local_1c._0_4_ = SUB84(Float2Int + dVar2,0);
  local_38 = iVar23;
  puVar12 = param_1->Buffer + ((param_1->Pane).y0 + local_1c._0_4_) * local_5c + (param_1->Pane).x0;
  p_Var17 = (_GRAPHIC_BUFFER *)(iVar23 * 0x18);
  local_4c = iVar23;
  local_34 = iVar23;
  local_1c = (double)*(float *)((int)&p_Var17->Height + (int)param_2) + Float2Int;
  local_20 = p_Var17;
  dVar2 = local_1c;
  dVar9 = (double)local_44;
  dVar8 = (double)local_48;
  dVar6 = (double)local_2c;
  dVar10 = (double)local_30;
  iVar23 = local_1c._0_4_;
  p_Var24 = p_Var17;
  param_1 = p_Var17;
  local_1c = dVar2;
  dVar2 = Float2Int;
  do {
    local_c = (double)*(float *)((int)&p_Var17->Height + (int)param_2) + dVar2;
    if (local_c._0_4_ <= iVar23) {
      do {
        iVar16 = local_4c;
        local_4c = aiStack_f0[local_4c + 1];
        if (local_4c == local_38) {
          return;
        }
        local_c = (double)param_2[local_4c].Vector.y + dVar2;
      } while (local_c._0_4_ <= iVar23);
      p_Var17 = (_GRAPHIC_BUFFER *)(local_4c * 0x18);
      pPVar18 = param_2 + iVar16;
      local_20 = p_Var17;
      fVar1 = 1.0 / (*(float *)((int)&p_Var17->Height + (int)param_2) - (pPVar18->Vector).y);
      local_c._0_4_ = SUB84((double)(pPVar18->Vector).y + dVar2,0);
      dVar9 = (double)local_c._0_4_ - (double)(pPVar18->Vector).y;
      local_40 = (*(float *)((int)&(param_2->Vector).x + (int)&p_Var17->Width) - (pPVar18->Vector).x
                 ) * fVar1;
      local_3c = (*(float *)((int)&p_Var17->Buffer + (int)param_2) -
                 (pPVar18->Texel).field2_0x8.luma) * fVar1;
      dVar8 = (double)local_40 * dVar9 + (double)(pPVar18->Vector).x;
      dVar9 = (double)local_3c * dVar9 + (double)(pPVar18->Texel).field2_0x8.luma;
    }
    local_c = (double)*(float *)((int)&p_Var24->Height + (int)param_2) + dVar2;
    if (local_c._0_4_ <= iVar23) {
      do {
        iVar16 = local_34;
        local_38 = local_34;
        local_34 = local_16c[local_34];
        local_c = (double)param_2[local_34].Vector.y + dVar2;
      } while (local_c._0_4_ <= iVar23);
      p_Var24 = (_GRAPHIC_BUFFER *)(local_34 * 0x18);
      pPVar18 = param_2 + iVar16;
      fVar1 = 1.0 / (*(float *)((int)&p_Var24->Height + (int)param_2) - (pPVar18->Vector).y);
      local_c._0_4_ = SUB84((double)(pPVar18->Vector).y + dVar2,0);
      dVar6 = (double)local_c._0_4_ - (double)(pPVar18->Vector).y;
      local_28 = (*(float *)((int)&(param_2->Vector).x + (int)&p_Var24->Width) - (pPVar18->Vector).x
                 ) * fVar1;
      local_24 = (*(float *)((int)&p_Var24->Buffer + (int)param_2) -
                 (pPVar18->Texel).field2_0x8.luma) * fVar1;
      dVar10 = (double)local_28 * dVar6 + (double)(pPVar18->Vector).x;
      dVar6 = (double)local_24 * dVar6 + (double)(pPVar18->Texel).field2_0x8.luma;
      param_1 = p_Var24;
    }
    dVar3 = dVar8 + dVar2;
    local_14 = dVar3;
    dVar3 = local_14;
    dVar4 = dVar10 + dVar2;
    local_58 = dVar4;
    dVar4 = local_58;
    local_58._0_4_ = SUB84(dVar4,0);
    local_14._0_4_ = SUB84(dVar3,0);
    iVar23 = (int)local_14;
    if ((int)local_14 != (int)local_58) {
      dVar7 = (dVar6 - dVar9) / (dVar10 - dVar8);
      local_6c = dVar7 + dVar2;
      if ((int)local_14 < (int)local_58) {
        dVar5 = ((double)(int)local_14 - dVar8) * dVar7 + dVar9;
        local_58 = dVar4;
        local_14 = dVar3;
      }
      else {
        local_14 = (double)CONCAT44((int)((ulonglong)dVar3 >> 0x20),(int)local_58);
        dVar3 = (double)(int)local_58;
        local_58 = (double)CONCAT44((int)((ulonglong)dVar4 >> 0x20),iVar23);
        dVar5 = (dVar3 - dVar10) * dVar7 + dVar6;
      }
      local_64 = dVar5 + dVar2;
      local_64._0_4_ = SUB84(dVar5 + dVar2,0);
      local_6c._0_4_ = SUB84(dVar7 + dVar2,0);
      uVar13 = local_64._0_4_ << 0x10 | local_64._0_4_ >> 0x10;
      uVar19 = local_6c._0_4_ << 0x10 | local_6c._0_4_ >> 0x10;
      local_58._0_4_ = (int)local_58 - (int)local_14;
      puVar25 = (uint *)(puVar12 + (int)local_14);
      uVar14 = param_4.Color & 0xff;
      p_Var17 = local_20;
      p_Var24 = param_1;
      if (7 < (int)local_58) {
        uVar21 = -(int)puVar25 & 3;
        local_58._0_4_ = (int)local_58 - uVar21;
        for (; puVar26 = puVar25, uVar21 != 0; uVar21 = uVar21 - 1) {
          uVar11 = (undefined1)uVar13;
          uVar15 = (undefined1)uVar14;
          uVar14 = (uint)CONCAT11(Luminance_Table[0][CONCAT11(uVar11,uVar15)],uVar15);
          uVar13 = uVar13 + uVar19 + (uint)CARRY4(uVar13,uVar19);
          *(uchar *)puVar25 = Luminance_Table[0][CONCAT11(uVar11,uVar15)];
          puVar25 = (uint *)((int)puVar25 + 1);
        }
        do {
          local_58._0_4_ = (int)local_58 + -4;
          uVar11 = (undefined1)uVar14;
          uVar14 = uVar13 + uVar19 + (uint)CARRY4(uVar13,uVar19);
          uVar20 = CONCAT11(Luminance_Table[0][CONCAT11((char)uVar14,uVar11)],
                            Luminance_Table[0][CONCAT11((char)uVar13,uVar11)]);
          uVar21 = uVar14 + uVar19 + (uint)CARRY4(uVar14,uVar19);
          uVar13 = uVar21 + uVar19 + (uint)CARRY4(uVar21,uVar19);
          uVar14 = (uint)CONCAT11((char)uVar13,uVar11);
          puVar25 = puVar26 + 1;
          uVar13 = uVar13 + uVar19 + (uint)CARRY4(uVar13,uVar19);
          *puVar26 = (uint)uVar20 |
                     CONCAT22(uVar20,CONCAT11(Luminance_Table[0][uVar14],
                                              Luminance_Table[0][CONCAT11((char)uVar21,uVar11)])) <<
                     0x10;
          puVar26 = puVar25;
        } while (3 < (int)local_58);
        dVar2 = Float2Int;
        if ((int)local_58 == 0) goto LAB_004fb955;
      }
      do {
        uVar11 = (undefined1)uVar13;
        uVar15 = (undefined1)uVar14;
        uVar13 = uVar13 + uVar19 + (uint)CARRY4(uVar13,uVar19);
        uVar14 = (uint)CONCAT11(Luminance_Table[0][CONCAT11(uVar11,uVar15)],uVar15);
        local_58._0_4_ = (int)local_58 + -1;
        *(uchar *)puVar25 = Luminance_Table[0][CONCAT11(uVar11,uVar15)];
        puVar25 = (uint *)((int)puVar25 + 1);
        dVar2 = Float2Int;
      } while ((int)local_58 != 0);
    }
LAB_004fb955:
    dVar10 = dVar10 + (double)local_28;
    puVar12 = puVar12 + local_5c;
    iVar23 = local_1c._0_4_ + 1;
    dVar6 = dVar6 + (double)local_24;
    local_1c = (double)CONCAT44(local_1c._4_4_,iVar23);
    dVar8 = dVar8 + (double)local_40;
    dVar9 = dVar9 + (double)local_3c;
  } while( true );
}
