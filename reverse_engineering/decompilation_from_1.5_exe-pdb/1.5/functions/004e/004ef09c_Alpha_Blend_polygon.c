/*
 * Entry: 004ef09c
 * Name: Alpha_Blend_polygon
 * Namespace: Global
 * Signature: void Alpha_Blend_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Alpha_Blend_polygon(_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  POINT_3D *pPVar7;
  uchar *puVar8;
  int iVar9;
  POINT_3D *pPVar10;
  POINT_3D *pPVar11;
  float *pfVar12;
  int iVar13;
  int local_144 [31];
  int aiStack_c8 [33];
  double local_44;
  int local_38;
  float local_34;
  float local_30;
  int local_2c;
  int local_28;
  float local_24;
  float local_20;
  undefined8 local_1c;
  double local_14;
  double local_c;
  
  pPVar7 = param_2;
  dVar3 = 100000.0;
  iVar13 = 0;
  iVar9 = 0;
  if (0 < param_3) {
    pfVar12 = &(param_2->Vector).y;
    do {
      fVar1 = *pfVar12;
      local_144[iVar9] = iVar9 + -1;
      aiStack_c8[iVar9 + 1] = iVar9 + 1;
      if ((double)fVar1 < dVar3 != ((double)fVar1 == dVar3)) {
        dVar3 = (double)*pfVar12;
        iVar13 = iVar9;
      }
      iVar9 = iVar9 + 1;
      pfVar12 = pfVar12 + 6;
    } while (iVar9 < param_3);
  }
  aiStack_c8[iVar9] = 0;
  local_144[0] = iVar9 + -1;
  local_14._0_4_ = SUB84(Float2Int + dVar3,0);
  iVar9 = param_1->Width;
  local_2c = iVar13;
  puVar8 = param_1->Buffer + ((param_1->Pane).y0 + local_14._0_4_) * iVar9 + (param_1->Pane).x0;
  pPVar10 = (POINT_3D *)(iVar13 * 0x18);
  local_38 = iVar13;
  local_28 = iVar13;
  local_14 = (double)*(float *)((int)&(pPVar10->Vector).y + (int)param_2) + Float2Int;
  dVar6 = (double)local_34;
  dVar5 = (double)local_24;
  param_2 = pPVar10;
  dVar3 = Float2Int;
  do {
    local_c = (double)*(float *)((int)&(pPVar10->Vector).y + (int)pPVar7) + dVar3;
    if (local_c._0_4_ <= local_14._0_4_) {
      do {
        iVar13 = local_38;
        local_38 = aiStack_c8[local_38 + 1];
        if (local_38 == local_2c) {
          return;
        }
        local_c = (double)pPVar7[local_38].Vector.y + dVar3;
      } while (local_c._0_4_ <= local_14._0_4_);
      pPVar11 = pPVar7 + iVar13;
      pPVar10 = (POINT_3D *)(local_38 * 0x18);
      local_30 = (*(float *)((int)&(pPVar10->Vector).x + (int)&(pPVar7->Vector).x) -
                 (pPVar11->Vector).x) *
                 (1.0 / (*(float *)((int)&(pPVar10->Vector).y + (int)pPVar7) - (pPVar11->Vector).y))
      ;
      local_c._0_4_ = SUB84((double)(pPVar11->Vector).y + dVar3,0);
      dVar6 = ((double)local_c._0_4_ - (double)(pPVar11->Vector).y) * (double)local_30 +
              (double)(pPVar11->Vector).x;
    }
    local_c = (double)*(float *)((int)&(param_2->Vector).y + (int)pPVar7) + dVar3;
    if (local_c._0_4_ <= local_14._0_4_) {
      do {
        local_2c = local_28;
        local_28 = local_144[local_2c];
        local_c = (double)pPVar7[local_28].Vector.y + dVar3;
      } while (local_c._0_4_ <= local_14._0_4_);
      param_2 = (POINT_3D *)(local_28 * 0x18);
      pPVar11 = pPVar7 + local_2c;
      pfVar12 = (float *)((int)&(param_2->Vector).x + (int)&(pPVar7->Vector).x);
      local_20 = (*pfVar12 - (pPVar11->Vector).x) * (1.0 / (pfVar12[1] - (pPVar11->Vector).y));
      local_c._0_4_ = SUB84((double)(pPVar11->Vector).y + dVar3,0);
      dVar5 = ((double)local_c._0_4_ - (double)(pPVar11->Vector).y) * (double)local_20 +
              (double)(pPVar11->Vector).x;
    }
    local_44 = dVar6 + dVar3;
    local_44._0_4_ = SUB84(dVar6 + dVar3,0);
    dVar4 = dVar5 + dVar3;
    local_1c = dVar4;
    dVar4 = local_1c;
    local_1c._0_4_ = SUB84(dVar4,0);
    iVar13 = (int)local_1c;
    if (local_44._0_4_ != (int)local_1c) {
      bVar2 = (int)local_1c < local_44._0_4_;
      local_1c = dVar4;
      if (bVar2) {
        local_1c = (double)CONCAT44((int)((ulonglong)dVar4 >> 0x20),local_44._0_4_);
        local_44._0_4_ = iVar13;
      }
      for (; local_44._0_4_ < (int)local_1c; local_44._0_4_ = local_44._0_4_ + 1) {
        puVar8[local_44._0_4_] =
             Headlight_Mask_Luma[param_4.Color & 0xff][(char)puVar8[local_44._0_4_]];
        dVar3 = Float2Int;
      }
    }
    dVar5 = dVar5 + (double)local_20;
    puVar8 = puVar8 + iVar9;
    local_14 = (double)CONCAT44(local_14._4_4_,local_14._0_4_ + 1);
    dVar6 = dVar6 + (double)local_30;
  } while( true );
}
