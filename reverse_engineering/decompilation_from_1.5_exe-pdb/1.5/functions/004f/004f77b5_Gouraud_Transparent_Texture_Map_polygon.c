/*
 * Entry: 004f77b5
 * Name: Gouraud_Transparent_Texture_Map_polygon
 * Namespace: Global
 * Signature: void Gouraud_Transparent_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Gouraud_Transparent_Texture_Map_polygon
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
  char **ppcVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  char *pcVar14;
  char *pcVar15;
  uchar *puVar16;
  uchar *local_6f4;
  POLYGON_SKIN local_6d4 [6];
  POLYGON_SKIN aPStack_6bc [180];
  POLYGON_SKIN aPStack_3ec [6];
  int aiStack_3d4 [192];
  double local_d4;
  double local_cc;
  double local_c4;
  double local_bc;
  double local_a4;
  double local_9c;
  double local_8c;
  double local_84;
  int local_74;
  int local_70;
  float local_6c;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  int local_44;
  int local_40;
  float local_3c;
  float local_34;
  float local_30;
  float local_28;
  float local_24;
  float local_20;
  undefined1 *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  if (Texture_Cache.Name != (TEXTURE *)param_4.Color) {
    Texture_Cache.Name = param_4.Texture;
    ppcVar9 = Texture_Cache.Address;
    pcVar14 = (char *)(param_4.Color + 8);
    iVar3 = *(int *)param_4.Texture;
    iVar10 = (param_4.Texture)->height;
    pcVar15 = pcVar14 + iVar3;
    pcVar12 = pcVar14 + iVar3 * 2;
    iVar3 = iVar3 * 3;
    iVar13 = iVar10 + 3;
    Texture_Cache.Padding[0] = pcVar14;
    Texture_Cache.Padding[1] = pcVar14;
    Texture_Cache.Padding[2] = pcVar14;
    Texture_Cache.Padding[3] = pcVar14;
    do {
      *ppcVar9 = pcVar14;
      ppcVar9[1] = pcVar15;
      ppcVar9[2] = pcVar12;
      pcVar14 = pcVar14 + iVar3;
      pcVar15 = pcVar15 + iVar3;
      pcVar12 = pcVar12 + iVar3;
      ppcVar9 = ppcVar9 + 3;
      bVar4 = 2 < iVar13;
      iVar13 = iVar13 + -3;
    } while (bVar4);
    pcVar14 = Texture_Cache.Padding[iVar10 + 3];
    Texture_Cache.Address[iVar10] = pcVar14;
    Texture_Cache.Address[iVar10 + 1] = pcVar14;
    Texture_Cache.Address[iVar10 + 2] = pcVar14;
    Texture_Cache.Address[iVar10 + 3] = pcVar14;
  }
  iVar10 = 100000;
  iVar3._0_2_ = *(short *)param_4;
  iVar3._2_2_ = *(short *)((int)param_4 + 2);
  fVar6 = ((float)(param_4.Texture)->height - UNITY) * UV_SCALE;
  fVar5 = ((float)iVar3 - UNITY) * UV_SCALE;
  PVar8.Color = 0;
  do {
    local_6d4[0] = PVar8;
    fVar1 = *(float *)((int)&(param_2->Texel).u + (int)local_6d4[0].Texture);
    fVar2 = *(float *)((int)&(param_2->Texel).v + (int)local_6d4[0].Texture);
    local_cc._0_4_ =
         SUB84((double)(*(float *)((int)&(param_2->Vector).y + (int)local_6d4[0].Texture) +
                       (float)Float2Int),0);
    ((POLYGON_SKIN *)((int)aPStack_3ec + (int)local_6d4[0].Texture))->Texture =
         (TEXTURE *)local_6d4[0];
    ((POLYGON_SKIN *)((int)aPStack_6bc + (int)local_6d4[0].Texture))->Texture =
         (TEXTURE *)local_6d4[0];
    *(float *)((int)&(param_2->Texel).u + (int)local_6d4[0].Texture) = fVar1 * fVar5;
    *(float *)((int)&(param_2->Texel).v + (int)local_6d4[0].Texture) = fVar2 * fVar6;
    PVar8.Texture = (TEXTURE *)(local_6d4[0].Color + 0x18);
    if (local_cc._0_4_ <= iVar10) {
      iVar10 = local_cc._0_4_;
      param_4.Texture = PVar8.Texture;
    }
  } while (PVar8.Color != param_3 * 0x18);
  iVar13 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_3ec + (int)PVar8.Texture) = 0;
  local_44 = iVar13;
  local_74 = iVar13;
  local_40 = iVar13;
  local_70 = iVar13;
  iVar3 = param_1->Width;
  local_d4 = (double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y) +
                     (float)Float2Int);
  local_6f4 = param_1->Buffer + ((param_1->Pane).y0 + iVar10) * iVar3 + (param_1->Pane).x0;
  do {
    local_cc = (double)(*(float *)((int)&(param_2->Vector).y + local_40) + (float)Float2Int);
    if (local_cc._0_4_ <= local_d4._0_4_) {
      do {
        iVar10 = local_40;
        local_40 = *(int *)((int)aiStack_3d4 + iVar10);
        if (local_40 == iVar13) {
          return;
        }
        local_cc = (double)(*(float *)((int)&(param_2->Vector).y + local_40) + (float)Float2Int);
      } while (local_cc._0_4_ <= local_d4._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_40) -
                      *(float *)((int)&(param_2->Vector).y + iVar10));
      local_24 = (*(float *)((int)&(param_2->Texel).v + local_40) -
                 *(float *)((int)&(param_2->Texel).v + iVar10)) * fVar5;
      local_cc._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar10) + (float)Float2Int),0);
      fVar6 = (float)local_cc._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar10);
      local_28 = (*(float *)((int)&(param_2->Texel).u + local_40) -
                 *(float *)((int)&(param_2->Texel).u + iVar10)) * fVar5;
      local_20 = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_40) -
                         *(float *)((int)&(param_2->Vector).x + iVar10));
      local_30 = local_24 * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar10);
      local_34 = local_28 * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar10);
      local_3c = fVar6 * local_20 + *(float *)((int)&(param_2->Vector).x + iVar10);
    }
    local_cc = (double)(*(float *)((int)&(param_2->Vector).y + local_70) + (float)Float2Int);
    if (local_cc._0_4_ <= local_d4._0_4_) {
      do {
        iVar10 = local_70;
        local_70 = *(int *)((int)local_6d4 + iVar10);
        local_cc = (double)(*(float *)((int)&(param_2->Vector).y + local_70) + (float)Float2Int);
      } while (local_cc._0_4_ <= local_d4._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_70) -
                      *(float *)((int)&(param_2->Vector).y + iVar10));
      local_54 = (*(float *)((int)&(param_2->Texel).v + local_70) -
                 *(float *)((int)&(param_2->Texel).v + iVar10)) * fVar5;
      local_cc._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar10) + (float)Float2Int),0);
      fVar6 = (float)local_cc._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar10);
      local_58 = (*(float *)((int)&(param_2->Texel).u + local_70) -
                 *(float *)((int)&(param_2->Texel).u + iVar10)) * fVar5;
      local_50 = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_70) -
                         *(float *)((int)&(param_2->Vector).x + iVar10));
      local_60 = local_54 * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar10);
      local_64 = local_58 * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar10);
      local_6c = fVar6 * local_50 + *(float *)((int)&(param_2->Vector).x + iVar10);
    }
    local_bc = (double)(local_3c + (float)Float2Int);
    local_c4 = (double)(local_6c + (float)Float2Int);
    local_bc._0_4_ = SUB84((double)(local_3c + (float)Float2Int),0);
    local_c4._0_4_ = SUB84((double)(local_6c + (float)Float2Int),0);
    if (local_bc._0_4_ != local_c4._0_4_) {
      fVar5 = UNITY / (local_6c - local_3c);
      fVar6 = fVar5 * (local_64 - local_34);
      if (local_bc._0_4_ < local_c4._0_4_) {
        dVar7 = (double)local_bc._0_4_ - (double)local_3c;
        iVar10 = local_bc._0_4_;
        fVar1 = local_34;
        fVar2 = local_30;
      }
      else {
        dVar7 = (double)local_c4._0_4_ - (double)local_6c;
        iVar10 = local_c4._0_4_;
        local_c4._0_4_ = local_bc._0_4_;
        fVar1 = local_64;
        fVar2 = local_60;
      }
      local_84 = (double)((local_60 - local_30) * fVar5);
      local_a4 = Float2Int + (double)fVar1 + (double)fVar6 * dVar7;
      local_9c = dVar7 * local_84 + Float2Int + (double)fVar2;
      local_84 = local_84 + Float2Int;
      local_c4._0_4_ = local_c4._0_4_ - iVar10;
      puVar16 = local_6f4 + iVar10;
      local_8c = (double)(fVar6 + (float)Float2Int);
      do {
        iVar10 = local_9c._0_4_ >> 0x10;
        iVar11 = local_a4._0_4_ >> 0x10;
        local_9c._0_4_ = local_9c._0_4_ + local_84._0_4_;
        local_a4._0_4_ = local_a4._0_4_ + local_8c._0_4_;
        *puVar16 = Texture_Cache.Address[iVar10][iVar11];
        puVar16 = puVar16 + 1;
        local_c4._0_4_ = local_c4._0_4_ + -1;
      } while (local_c4._0_4_ != 0);
    }
    local_3c = local_3c + local_20;
    local_34 = local_34 + local_28;
    local_30 = local_30 + local_24;
    local_6f4 = local_6f4 + iVar3;
    local_d4._0_4_ = local_d4._0_4_ + 1;
    local_6c = local_6c + local_50;
    local_64 = local_64 + local_58;
    local_60 = local_60 + local_54;
  } while( true );
}
