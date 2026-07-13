/*
 * Entry: 005019f5
 * Name: Tile_Texture_Map_polygon
 * Namespace: Global
 * Signature: void Tile_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Tile_Texture_Map_polygon
          (_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  POLYGON_SKIN PVar9;
  uint uVar10;
  int iVar11;
  char **ppcVar12;
  int iVar13;
  uint uVar14;
  char *pcVar15;
  int iVar16;
  char *pcVar17;
  char *pcVar18;
  uchar *puVar19;
  int local_6f0;
  uchar *local_6d4;
  POLYGON_SKIN local_6b4 [6];
  POLYGON_SKIN aPStack_69c [180];
  POLYGON_SKIN aPStack_3cc [6];
  int aiStack_3b4 [192];
  double local_b4;
  double local_ac;
  double local_a4;
  double local_9c;
  double local_94;
  double local_8c;
  double local_84;
  double local_7c;
  int local_64;
  int local_60;
  float local_5c;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  int local_3c;
  int local_38;
  float local_34;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined1 *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  if (Texture_Cache.Name != (TEXTURE *)param_4.Color) {
    Texture_Cache.Name = param_4.Texture;
    ppcVar12 = Texture_Cache.Address;
    pcVar17 = (char *)(param_4.Color + 8);
    iVar3 = *(int *)param_4.Texture;
    pcVar18 = pcVar17 + iVar3;
    pcVar15 = pcVar17 + iVar3 * 2;
    iVar3 = iVar3 * 3;
    iVar11 = (param_4.Texture)->height + 3;
    Texture_Cache.Padding[0] = pcVar17;
    Texture_Cache.Padding[1] = pcVar17;
    Texture_Cache.Padding[2] = pcVar17;
    Texture_Cache.Padding[3] = pcVar17;
    do {
      *ppcVar12 = pcVar17;
      ppcVar12[1] = pcVar18;
      ppcVar12[2] = pcVar15;
      pcVar17 = pcVar17 + iVar3;
      pcVar18 = pcVar18 + iVar3;
      pcVar15 = pcVar15 + iVar3;
      ppcVar12 = ppcVar12 + 3;
      bVar5 = 2 < iVar11;
      iVar11 = iVar11 + -3;
    } while (bVar5);
    pcVar17 = Texture_Cache.Padding[local_6f0 + 3];
    Texture_Cache.Address[local_6f0] = pcVar17;
    Texture_Cache.Address[local_6f0 + 1] = pcVar17;
    Texture_Cache.Address[local_6f0 + 2] = pcVar17;
    Texture_Cache.Address[local_6f0 + 3] = pcVar17;
  }
  iVar11 = *(int *)param_4.Texture;
  iVar4 = (param_4.Texture)->height;
  iVar13 = 100000;
  iVar3._0_2_ = *(short *)param_4;
  iVar3._2_2_ = *(short *)((int)param_4 + 2);
  fVar6 = (float)(param_4.Texture)->height * UV_SCALE;
  fVar7 = (float)iVar3 * UV_SCALE;
  PVar9.Color = 0;
  do {
    local_6b4[0] = PVar9;
    fVar1 = *(float *)((int)&(param_2->Texel).u + (int)local_6b4[0].Texture);
    fVar2 = *(float *)((int)&(param_2->Texel).v + (int)local_6b4[0].Texture);
    local_ac._0_4_ =
         SUB84((double)(*(float *)((int)&(param_2->Vector).y + (int)local_6b4[0].Texture) +
                       (float)Float2Int),0);
    ((POLYGON_SKIN *)((int)aPStack_3cc + (int)local_6b4[0].Texture))->Texture =
         (TEXTURE *)local_6b4[0];
    ((POLYGON_SKIN *)((int)aPStack_69c + (int)local_6b4[0].Texture))->Texture =
         (TEXTURE *)local_6b4[0];
    *(float *)((int)&(param_2->Texel).u + (int)local_6b4[0].Texture) = fVar1 * fVar7;
    *(float *)((int)&(param_2->Texel).v + (int)local_6b4[0].Texture) = fVar2 * fVar6;
    PVar9.Texture = (TEXTURE *)(local_6b4[0].Color + 0x18);
    if (local_ac._0_4_ <= iVar13) {
      iVar13 = local_ac._0_4_;
      param_4.Texture = PVar9.Texture;
    }
  } while (PVar9.Color != param_3 * 0x18);
  iVar16 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_3cc + (int)PVar9.Texture) = 0;
  local_3c = iVar16;
  local_64 = iVar16;
  local_38 = iVar16;
  local_60 = iVar16;
  iVar3 = param_1->Width;
  local_b4 = (double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y) +
                     (float)Float2Int);
  local_6d4 = param_1->Buffer + ((param_1->Pane).y0 + iVar13) * iVar3 + (param_1->Pane).x0;
  do {
    local_ac = (double)(*(float *)((int)&(param_2->Vector).y + local_38) + (float)Float2Int);
    if (local_ac._0_4_ <= local_b4._0_4_) {
      do {
        iVar13 = local_38;
        local_38 = *(int *)((int)aiStack_3b4 + iVar13);
        if (local_38 == iVar16) {
          return;
        }
        local_ac = (double)(*(float *)((int)&(param_2->Vector).y + local_38) + (float)Float2Int);
      } while (local_ac._0_4_ <= local_b4._0_4_);
      fVar6 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_38) -
                      *(float *)((int)&(param_2->Vector).y + iVar13));
      local_20 = (*(float *)((int)&(param_2->Texel).v + local_38) -
                 *(float *)((int)&(param_2->Texel).v + iVar13)) * fVar6;
      local_ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar13) + (float)Float2Int),0);
      fVar7 = (float)local_ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar13);
      local_24 = (*(float *)((int)&(param_2->Texel).u + local_38) -
                 *(float *)((int)&(param_2->Texel).u + iVar13)) * fVar6;
      local_1c = fVar6 * (*(float *)((int)&(param_2->Vector).x + local_38) -
                         *(float *)((int)&(param_2->Vector).x + iVar13));
      local_28 = local_20 * fVar7 + *(float *)((int)&(param_2->Texel).v + iVar13);
      local_2c = local_24 * fVar7 + *(float *)((int)&(param_2->Texel).u + iVar13);
      local_34 = fVar7 * local_1c + *(float *)((int)&(param_2->Vector).x + iVar13);
    }
    local_ac = (double)(*(float *)((int)&(param_2->Vector).y + local_60) + (float)Float2Int);
    if (local_ac._0_4_ <= local_b4._0_4_) {
      do {
        iVar13 = local_60;
        local_60 = *(int *)((int)local_6b4 + iVar13);
        local_ac = (double)(*(float *)((int)&(param_2->Vector).y + local_60) + (float)Float2Int);
      } while (local_ac._0_4_ <= local_b4._0_4_);
      fVar6 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_60) -
                      *(float *)((int)&(param_2->Vector).y + iVar13));
      local_48 = (*(float *)((int)&(param_2->Texel).v + local_60) -
                 *(float *)((int)&(param_2->Texel).v + iVar13)) * fVar6;
      local_ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar13) + (float)Float2Int),0);
      fVar7 = (float)local_ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar13);
      local_4c = (*(float *)((int)&(param_2->Texel).u + local_60) -
                 *(float *)((int)&(param_2->Texel).u + iVar13)) * fVar6;
      local_44 = fVar6 * (*(float *)((int)&(param_2->Vector).x + local_60) -
                         *(float *)((int)&(param_2->Vector).x + iVar13));
      local_50 = local_48 * fVar7 + *(float *)((int)&(param_2->Texel).v + iVar13);
      local_54 = local_4c * fVar7 + *(float *)((int)&(param_2->Texel).u + iVar13);
      local_5c = fVar7 * local_44 + *(float *)((int)&(param_2->Vector).x + iVar13);
    }
    local_9c = (double)(local_34 + (float)Float2Int);
    local_a4 = (double)(local_5c + (float)Float2Int);
    local_9c._0_4_ = SUB84((double)(local_34 + (float)Float2Int),0);
    local_a4._0_4_ = SUB84((double)(local_5c + (float)Float2Int),0);
    if (local_9c._0_4_ != local_a4._0_4_) {
      fVar6 = UNITY / (local_5c - local_34);
      fVar7 = fVar6 * (local_54 - local_2c);
      if (local_9c._0_4_ < local_a4._0_4_) {
        dVar8 = (double)local_9c._0_4_ - (double)local_34;
        iVar13 = local_9c._0_4_;
        fVar1 = local_2c;
        fVar2 = local_28;
      }
      else {
        dVar8 = (double)local_a4._0_4_ - (double)local_5c;
        iVar13 = local_a4._0_4_;
        local_a4._0_4_ = local_9c._0_4_;
        fVar1 = local_54;
        fVar2 = local_50;
      }
      local_7c = (double)((local_50 - local_28) * fVar6);
      local_94 = Float2Int + (double)fVar1 + (double)fVar7 * dVar8;
      local_84 = dVar8 * local_7c + Float2Int + (double)fVar2;
      local_7c = local_7c + Float2Int;
      local_a4._0_4_ = local_a4._0_4_ - iVar13;
      puVar19 = local_6d4 + iVar13;
      local_8c = (double)(fVar7 + (float)Float2Int);
      do {
        uVar10 = local_84._0_4_ >> 0x10;
        uVar14 = local_94._0_4_ >> 0x10;
        local_84._0_4_ = local_84._0_4_ + local_7c._0_4_;
        local_94._0_4_ = local_94._0_4_ + local_8c._0_4_;
        *puVar19 = Texture_Cache.Address[uVar10 & iVar4 - 1U][uVar14 & iVar11 - 1U];
        puVar19 = puVar19 + 1;
        local_a4._0_4_ = local_a4._0_4_ + -1;
      } while (local_a4._0_4_ != 0);
    }
    local_34 = local_34 + local_1c;
    local_2c = local_2c + local_24;
    local_28 = local_28 + local_20;
    local_6d4 = local_6d4 + iVar3;
    local_b4._0_4_ = local_b4._0_4_ + 1;
    local_5c = local_5c + local_44;
    local_54 = local_54 + local_4c;
    local_50 = local_50 + local_48;
  } while( true );
}
