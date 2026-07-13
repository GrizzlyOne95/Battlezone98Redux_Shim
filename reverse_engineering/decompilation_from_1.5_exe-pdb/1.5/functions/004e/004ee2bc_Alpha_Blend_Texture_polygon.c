/*
 * Entry: 004ee2bc
 * Name: Alpha_Blend_Texture_polygon
 * Namespace: Global
 * Signature: void Alpha_Blend_Texture_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Alpha_Blend_Texture_polygon
          (_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  POLYGON_SKIN PVar8;
  int iVar9;
  char **ppcVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  int iVar14;
  char *pcVar15;
  char *pcVar16;
  uchar *puVar17;
  uchar *local_6d0;
  POLYGON_SKIN local_6b0 [6];
  POLYGON_SKIN aPStack_698 [180];
  POLYGON_SKIN aPStack_3c8 [6];
  int aiStack_3b0 [192];
  double local_b0;
  double local_a8;
  double local_a0;
  double local_98;
  double local_90;
  double local_88;
  double local_80;
  double local_78;
  int local_60;
  int local_5c;
  float local_58;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  int local_38;
  int local_34;
  float local_30;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  if (Texture_Cache.Name != (TEXTURE *)param_4.Color) {
    Texture_Cache.Name = param_4.Texture;
    ppcVar10 = Texture_Cache.Address;
    pcVar15 = (char *)(param_4.Color + 8);
    iVar3 = *(int *)param_4.Texture;
    iVar11 = (param_4.Texture)->height;
    pcVar16 = pcVar15 + iVar3;
    pcVar13 = pcVar15 + iVar3 * 2;
    iVar3 = iVar3 * 3;
    iVar14 = iVar11 + 3;
    Texture_Cache.Padding[0] = pcVar15;
    Texture_Cache.Padding[1] = pcVar15;
    Texture_Cache.Padding[2] = pcVar15;
    Texture_Cache.Padding[3] = pcVar15;
    do {
      *ppcVar10 = pcVar15;
      ppcVar10[1] = pcVar16;
      ppcVar10[2] = pcVar13;
      pcVar15 = pcVar15 + iVar3;
      pcVar16 = pcVar16 + iVar3;
      pcVar13 = pcVar13 + iVar3;
      ppcVar10 = ppcVar10 + 3;
      bVar4 = 2 < iVar14;
      iVar14 = iVar14 + -3;
    } while (bVar4);
    pcVar15 = Texture_Cache.Padding[iVar11 + 3];
    Texture_Cache.Address[iVar11] = pcVar15;
    Texture_Cache.Address[iVar11 + 1] = pcVar15;
    Texture_Cache.Address[iVar11 + 2] = pcVar15;
    Texture_Cache.Address[iVar11 + 3] = pcVar15;
  }
  iVar11 = 100000;
  iVar3._0_2_ = *(short *)param_4;
  iVar3._2_2_ = *(short *)((int)param_4 + 2);
  fVar6 = ((float)(param_4.Texture)->height - UNITY) * UV_SCALE;
  fVar5 = ((float)iVar3 - UNITY) * UV_SCALE;
  PVar8.Color = 0;
  do {
    local_6b0[0] = PVar8;
    fVar1 = *(float *)((int)&(param_2->Texel).u + (int)local_6b0[0].Texture);
    fVar2 = *(float *)((int)&(param_2->Texel).v + (int)local_6b0[0].Texture);
    local_a8._0_4_ =
         SUB84((double)(*(float *)((int)&(param_2->Vector).y + (int)local_6b0[0].Texture) +
                       (float)Float2Int),0);
    ((POLYGON_SKIN *)((int)aPStack_3c8 + (int)local_6b0[0].Texture))->Texture =
         (TEXTURE *)local_6b0[0];
    ((POLYGON_SKIN *)((int)aPStack_698 + (int)local_6b0[0].Texture))->Texture =
         (TEXTURE *)local_6b0[0];
    *(float *)((int)&(param_2->Texel).u + (int)local_6b0[0].Texture) = fVar1 * fVar5;
    *(float *)((int)&(param_2->Texel).v + (int)local_6b0[0].Texture) = fVar2 * fVar6;
    PVar8.Texture = (TEXTURE *)(local_6b0[0].Color + 0x18);
    if (local_a8._0_4_ <= iVar11) {
      iVar11 = local_a8._0_4_;
      param_4.Texture = PVar8.Texture;
    }
  } while (PVar8.Color != param_3 * 0x18);
  iVar14 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_3c8 + (int)PVar8.Texture) = 0;
  local_38 = iVar14;
  local_60 = iVar14;
  local_34 = iVar14;
  local_5c = iVar14;
  iVar3 = param_1->Width;
  local_b0 = (double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y) +
                     (float)Float2Int);
  local_6d0 = param_1->Buffer + ((param_1->Pane).y0 + iVar11) * iVar3 + (param_1->Pane).x0;
  do {
    local_a8 = (double)(*(float *)((int)&(param_2->Vector).y + local_34) + (float)Float2Int);
    if (local_a8._0_4_ <= local_b0._0_4_) {
      do {
        iVar11 = local_34;
        local_34 = *(int *)((int)aiStack_3b0 + iVar11);
        if (local_34 == iVar14) {
          return;
        }
        local_a8 = (double)(*(float *)((int)&(param_2->Vector).y + local_34) + (float)Float2Int);
      } while (local_a8._0_4_ <= local_b0._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_34) -
                      *(float *)((int)&(param_2->Vector).y + iVar11));
      local_1c = (*(float *)((int)&(param_2->Texel).v + local_34) -
                 *(float *)((int)&(param_2->Texel).v + iVar11)) * fVar5;
      local_a8._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar11) + (float)Float2Int),0);
      fVar6 = (float)local_a8._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar11);
      local_20 = (*(float *)((int)&(param_2->Texel).u + local_34) -
                 *(float *)((int)&(param_2->Texel).u + iVar11)) * fVar5;
      local_18 = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_34) -
                         *(float *)((int)&(param_2->Vector).x + iVar11));
      local_24 = local_1c * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar11);
      local_28 = local_20 * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar11);
      local_30 = fVar6 * local_18 + *(float *)((int)&(param_2->Vector).x + iVar11);
    }
    local_a8 = (double)(*(float *)((int)&(param_2->Vector).y + local_5c) + (float)Float2Int);
    if (local_a8._0_4_ <= local_b0._0_4_) {
      do {
        iVar11 = local_5c;
        local_5c = *(int *)((int)local_6b0 + iVar11);
        local_a8 = (double)(*(float *)((int)&(param_2->Vector).y + local_5c) + (float)Float2Int);
      } while (local_a8._0_4_ <= local_b0._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_5c) -
                      *(float *)((int)&(param_2->Vector).y + iVar11));
      local_44 = (*(float *)((int)&(param_2->Texel).v + local_5c) -
                 *(float *)((int)&(param_2->Texel).v + iVar11)) * fVar5;
      local_a8._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar11) + (float)Float2Int),0);
      fVar6 = (float)local_a8._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar11);
      local_48 = (*(float *)((int)&(param_2->Texel).u + local_5c) -
                 *(float *)((int)&(param_2->Texel).u + iVar11)) * fVar5;
      local_40 = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_5c) -
                         *(float *)((int)&(param_2->Vector).x + iVar11));
      local_4c = local_44 * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar11);
      local_50 = local_48 * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar11);
      local_58 = fVar6 * local_40 + *(float *)((int)&(param_2->Vector).x + iVar11);
    }
    local_98 = (double)(local_30 + (float)Float2Int);
    local_a0 = (double)(local_58 + (float)Float2Int);
    local_98._0_4_ = SUB84((double)(local_30 + (float)Float2Int),0);
    local_a0._0_4_ = SUB84((double)(local_58 + (float)Float2Int),0);
    if (local_98._0_4_ != local_a0._0_4_) {
      fVar5 = UNITY / (local_58 - local_30);
      fVar6 = fVar5 * (local_50 - local_28);
      if (local_98._0_4_ < local_a0._0_4_) {
        dVar7 = (double)local_98._0_4_ - (double)local_30;
        iVar11 = local_98._0_4_;
        fVar1 = local_28;
        fVar2 = local_24;
      }
      else {
        dVar7 = (double)local_a0._0_4_ - (double)local_58;
        iVar11 = local_a0._0_4_;
        local_a0._0_4_ = local_98._0_4_;
        fVar1 = local_50;
        fVar2 = local_4c;
      }
      local_78 = (double)((local_4c - local_24) * fVar5);
      local_90 = Float2Int + (double)fVar1 + (double)fVar6 * dVar7;
      local_80 = dVar7 * local_78 + Float2Int + (double)fVar2;
      local_78 = local_78 + Float2Int;
      local_a0._0_4_ = local_a0._0_4_ - iVar11;
      local_88 = (double)(fVar6 + (float)Float2Int);
      puVar17 = local_6d0 + iVar11;
      do {
        while( true ) {
          iVar9 = local_80._0_4_ >> 0x10;
          iVar12 = local_90._0_4_ >> 0x10;
          local_80._0_4_ = local_80._0_4_ + local_78._0_4_;
          iVar11 = local_90._0_4_ >> 0x1f;
          local_90._0_4_ = local_90._0_4_ + local_88._0_4_;
          if (Texture_Cache.Address[iVar9][iVar12] != -1) break;
          local_a0._0_4_ = local_a0._0_4_ + -1;
          puVar17 = puVar17 + 1;
          if (local_a0._0_4_ == 0) goto LAB_004ee7a9;
        }
        local_a0._0_4_ = local_a0._0_4_ + -1;
        *puVar17 = Headlight_Mask_Luma[0]
                   [CONCAT31(CONCAT21((short)iVar11,Texture_Cache.Address[iVar9][iVar12]),*puVar17)]
        ;
        puVar17 = puVar17 + 1;
      } while (local_a0._0_4_ != 0);
    }
LAB_004ee7a9:
    local_30 = local_30 + local_18;
    local_28 = local_28 + local_20;
    local_24 = local_24 + local_1c;
    local_6d0 = local_6d0 + iVar3;
    local_b0._0_4_ = local_b0._0_4_ + 1;
    local_58 = local_58 + local_40;
    local_50 = local_50 + local_48;
    local_4c = local_4c + local_44;
  } while( true );
}
