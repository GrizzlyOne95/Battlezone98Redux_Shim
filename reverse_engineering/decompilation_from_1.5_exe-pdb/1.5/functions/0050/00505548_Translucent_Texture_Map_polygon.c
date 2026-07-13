/*
 * Entry: 00505548
 * Name: Translucent_Texture_Map_polygon
 * Namespace: Global
 * Signature: void Translucent_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Translucent_Texture_Map_polygon
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
  uchar *local_7d4;
  POLYGON_SKIN local_7b4 [6];
  POLYGON_SKIN aPStack_79c [180];
  POLYGON_SKIN aPStack_4cc [6];
  int aiStack_4b4 [192];
  double local_1b4;
  double local_1ac;
  double local_1a4;
  double local_19c;
  double local_194;
  double local_18c;
  double local_184;
  double local_17c;
  int local_164;
  int local_160;
  float local_15c;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  int local_13c;
  int local_138;
  float local_134;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  undefined1 *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
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
    local_7b4[0] = PVar8;
    fVar1 = *(float *)((int)&(param_2->Texel).u + (int)local_7b4[0].Texture);
    fVar2 = *(float *)((int)&(param_2->Texel).v + (int)local_7b4[0].Texture);
    local_1ac._0_4_ =
         SUB84((double)(*(float *)((int)&(param_2->Vector).y + (int)local_7b4[0].Texture) +
                       (float)Float2Int),0);
    ((POLYGON_SKIN *)((int)aPStack_4cc + (int)local_7b4[0].Texture))->Texture =
         (TEXTURE *)local_7b4[0];
    ((POLYGON_SKIN *)((int)aPStack_79c + (int)local_7b4[0].Texture))->Texture =
         (TEXTURE *)local_7b4[0];
    *(float *)((int)&(param_2->Texel).u + (int)local_7b4[0].Texture) = fVar1 * fVar5;
    *(float *)((int)&(param_2->Texel).v + (int)local_7b4[0].Texture) = fVar2 * fVar6;
    PVar8.Texture = (TEXTURE *)(local_7b4[0].Color + 0x18);
    if (local_1ac._0_4_ <= iVar11) {
      iVar11 = local_1ac._0_4_;
      param_4.Texture = PVar8.Texture;
    }
  } while (PVar8.Color != param_3 * 0x18);
  iVar14 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_4cc + (int)PVar8.Texture) = 0;
  local_13c = iVar14;
  local_164 = iVar14;
  local_138 = iVar14;
  local_160 = iVar14;
  iVar3 = param_1->Width;
  local_1b4 = (double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y) +
                      (float)Float2Int);
  local_7d4 = param_1->Buffer + ((param_1->Pane).y0 + iVar11) * iVar3 + (param_1->Pane).x0;
  do {
    local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_138) + (float)Float2Int);
    if (local_1ac._0_4_ <= local_1b4._0_4_) {
      do {
        iVar11 = local_138;
        local_138 = *(int *)((int)aiStack_4b4 + iVar11);
        if (local_138 == iVar14) {
          return;
        }
        local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_138) + (float)Float2Int);
      } while (local_1ac._0_4_ <= local_1b4._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_138) -
                      *(float *)((int)&(param_2->Vector).y + iVar11));
      local_120 = (*(float *)((int)&(param_2->Texel).v + local_138) -
                  *(float *)((int)&(param_2->Texel).v + iVar11)) * fVar5;
      local_1ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar11) + (float)Float2Int),0);
      fVar6 = (float)local_1ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar11);
      local_124 = (*(float *)((int)&(param_2->Texel).u + local_138) -
                  *(float *)((int)&(param_2->Texel).u + iVar11)) * fVar5;
      local_11c = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_138) -
                          *(float *)((int)&(param_2->Vector).x + iVar11));
      local_128 = local_120 * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar11);
      local_12c = local_124 * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar11);
      local_134 = fVar6 * local_11c + *(float *)((int)&(param_2->Vector).x + iVar11);
    }
    local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_160) + (float)Float2Int);
    if (local_1ac._0_4_ <= local_1b4._0_4_) {
      do {
        iVar11 = local_160;
        local_160 = *(int *)((int)local_7b4 + iVar11);
        local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_160) + (float)Float2Int);
      } while (local_1ac._0_4_ <= local_1b4._0_4_);
      fVar5 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_160) -
                      *(float *)((int)&(param_2->Vector).y + iVar11));
      local_148 = (*(float *)((int)&(param_2->Texel).v + local_160) -
                  *(float *)((int)&(param_2->Texel).v + iVar11)) * fVar5;
      local_1ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar11) + (float)Float2Int),0);
      fVar6 = (float)local_1ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar11);
      local_14c = (*(float *)((int)&(param_2->Texel).u + local_160) -
                  *(float *)((int)&(param_2->Texel).u + iVar11)) * fVar5;
      local_144 = fVar5 * (*(float *)((int)&(param_2->Vector).x + local_160) -
                          *(float *)((int)&(param_2->Vector).x + iVar11));
      local_150 = local_148 * fVar6 + *(float *)((int)&(param_2->Texel).v + iVar11);
      local_154 = local_14c * fVar6 + *(float *)((int)&(param_2->Texel).u + iVar11);
      local_15c = fVar6 * local_144 + *(float *)((int)&(param_2->Vector).x + iVar11);
    }
    local_19c = (double)(local_134 + (float)Float2Int);
    local_1a4 = (double)(local_15c + (float)Float2Int);
    local_19c._0_4_ = SUB84((double)(local_134 + (float)Float2Int),0);
    local_1a4._0_4_ = SUB84((double)(local_15c + (float)Float2Int),0);
    if (local_19c._0_4_ != local_1a4._0_4_) {
      fVar5 = UNITY / (local_15c - local_134);
      fVar6 = fVar5 * (local_154 - local_12c);
      if (local_19c._0_4_ < local_1a4._0_4_) {
        dVar7 = (double)local_19c._0_4_ - (double)local_134;
        iVar11 = local_19c._0_4_;
        fVar1 = local_12c;
        fVar2 = local_128;
      }
      else {
        dVar7 = (double)local_1a4._0_4_ - (double)local_15c;
        iVar11 = local_1a4._0_4_;
        local_1a4._0_4_ = local_19c._0_4_;
        fVar1 = local_154;
        fVar2 = local_150;
      }
      local_17c = (double)((local_150 - local_128) * fVar5);
      local_194 = Float2Int + (double)fVar1 + (double)fVar6 * dVar7;
      local_184 = dVar7 * local_17c + Float2Int + (double)fVar2;
      local_17c = local_17c + Float2Int;
      local_1a4._0_4_ = local_1a4._0_4_ - iVar11;
      local_18c = (double)(fVar6 + (float)Float2Int);
      puVar17 = local_7d4 + iVar11;
      do {
        iVar9 = local_184._0_4_ >> 0x10;
        iVar12 = local_194._0_4_ >> 0x10;
        local_184._0_4_ = local_184._0_4_ + local_17c._0_4_;
        iVar11 = local_194._0_4_ >> 0x1f;
        local_194._0_4_ = local_194._0_4_ + local_18c._0_4_;
        local_1a4._0_4_ = local_1a4._0_4_ + -1;
        *puVar17 = Translucency_Table[0]
                   [CONCAT31(CONCAT21((short)iVar11,Texture_Cache.Address[iVar9][iVar12]),*puVar17)]
        ;
        puVar17 = puVar17 + 1;
      } while (local_1a4._0_4_ != 0);
    }
    local_134 = local_134 + local_11c;
    local_12c = local_12c + local_124;
    local_128 = local_128 + local_120;
    local_7d4 = local_7d4 + iVar3;
    local_1b4._0_4_ = local_1b4._0_4_ + 1;
    local_15c = local_15c + local_144;
    local_154 = local_154 + local_14c;
    local_150 = local_150 + local_148;
  } while( true );
}
