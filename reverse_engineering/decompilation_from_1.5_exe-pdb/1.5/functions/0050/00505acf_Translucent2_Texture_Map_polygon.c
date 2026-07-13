/*
 * Entry: 00505acf
 * Name: Translucent2_Texture_Map_polygon
 * Namespace: Global
 * Signature: void Translucent2_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Translucent2_Texture_Map_polygon
          (_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  int extraout_EAX;
  POLYGON_SKIN PVar14;
  char **ppcVar15;
  int iVar16;
  char *pcVar17;
  int iVar18;
  char *pcVar19;
  int iVar20;
  char *pcVar21;
  uchar *puVar22;
  uchar *in_stack_fffff814;
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
  Save_Translucency_Key_Color(in_stack_fffff814);
  if (extraout_EAX != param_4.Color) {
    Texture_Cache.Name = param_4.Texture;
    ppcVar15 = Texture_Cache.Address;
    pcVar19 = (char *)(param_4.Color + 8);
    iVar3 = *(int *)param_4.Texture;
    iVar16 = (param_4.Texture)->height;
    pcVar21 = pcVar19 + iVar3;
    pcVar17 = pcVar19 + iVar3 * 2;
    iVar3 = iVar3 * 3;
    iVar18 = iVar16 + 3;
    Texture_Cache.Padding[0] = pcVar19;
    Texture_Cache.Padding[1] = pcVar19;
    Texture_Cache.Padding[2] = pcVar19;
    Texture_Cache.Padding[3] = pcVar19;
    do {
      *ppcVar15 = pcVar19;
      ppcVar15[1] = pcVar21;
      ppcVar15[2] = pcVar17;
      pcVar19 = pcVar19 + iVar3;
      pcVar21 = pcVar21 + iVar3;
      pcVar17 = pcVar17 + iVar3;
      ppcVar15 = ppcVar15 + 3;
      bVar4 = 2 < iVar18;
      iVar18 = iVar18 + -3;
    } while (bVar4);
    pcVar19 = Texture_Cache.Padding[iVar16 + 3];
    Texture_Cache.Address[iVar16] = pcVar19;
    Texture_Cache.Address[iVar16 + 1] = pcVar19;
    Texture_Cache.Address[iVar16 + 2] = pcVar19;
    Texture_Cache.Address[iVar16 + 3] = pcVar19;
  }
  iVar16 = 100000;
  iVar3._0_2_ = *(short *)param_4;
  iVar3._2_2_ = *(short *)((int)param_4 + 2);
  fVar6 = ((float)(param_4.Texture)->height - UNITY) * UV_SCALE;
  fVar5 = ((float)iVar3 - UNITY) * UV_SCALE;
  PVar14.Color = 0;
  do {
    local_7b4[0] = PVar14;
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
    PVar14.Texture = (TEXTURE *)(local_7b4[0].Color + 0x18);
    if (local_1ac._0_4_ <= iVar16) {
      iVar16 = local_1ac._0_4_;
      param_4.Texture = PVar14.Texture;
    }
  } while (PVar14.Color != param_3 * 0x18);
  iVar18 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_4cc + (int)PVar14.Texture) = 0;
  local_13c = iVar18;
  local_164 = iVar18;
  local_138 = iVar18;
  local_160 = iVar18;
  iVar3 = param_1->Width;
  local_1b4 = (double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y) +
                      (float)Float2Int);
  dVar7 = local_1b4;
  local_7d4 = param_1->Buffer + ((param_1->Pane).y0 + iVar16) * iVar3 + (param_1->Pane).x0;
  do {
    local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_138) + (float)Float2Int);
    dVar8 = local_1ac;
    bVar4 = local_1ac._0_4_ <= local_1b4._0_4_;
    local_1ac = dVar8;
    if (bVar4) {
      do {
        iVar16 = local_138;
        local_138 = *(int *)((int)aiStack_4b4 + iVar16);
        if (local_138 == iVar18) {
          local_1b4 = dVar7;
          Restore_Translucency_Key_Color((uchar *)param_2);
          return;
        }
        local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_138) + (float)Float2Int);
        dVar8 = local_1ac;
        bVar4 = local_1ac._0_4_ <= local_1b4._0_4_;
        local_1ac = dVar8;
      } while (bVar4);
      local_11c = UNITY / (*(float *)((int)&(param_2->Vector).y + local_138) -
                          *(float *)((int)&(param_2->Vector).y + iVar16));
      local_120 = (*(float *)((int)&(param_2->Texel).v + local_138) -
                  *(float *)((int)&(param_2->Texel).v + iVar16)) * local_11c;
      local_1ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar16) + (float)Float2Int),0);
      fVar5 = (float)local_1ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar16);
      local_124 = (*(float *)((int)&(param_2->Texel).u + local_138) -
                  *(float *)((int)&(param_2->Texel).u + iVar16)) * local_11c;
      local_11c = local_11c *
                  (*(float *)((int)&(param_2->Vector).x + local_138) -
                  *(float *)((int)&(param_2->Vector).x + iVar16));
      local_128 = local_120 * fVar5 + *(float *)((int)&(param_2->Texel).v + iVar16);
      local_12c = local_124 * fVar5 + *(float *)((int)&(param_2->Texel).u + iVar16);
      local_134 = fVar5 * local_11c + *(float *)((int)&(param_2->Vector).x + iVar16);
    }
    local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_160) + (float)Float2Int);
    if (local_1ac._0_4_ <= local_1b4._0_4_) {
      do {
        iVar16 = local_160;
        local_160 = *(int *)((int)local_7b4 + iVar16);
        local_1ac = (double)(*(float *)((int)&(param_2->Vector).y + local_160) + (float)Float2Int);
      } while (local_1ac._0_4_ <= local_1b4._0_4_);
      local_144 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_160) -
                          *(float *)((int)&(param_2->Vector).y + iVar16));
      local_148 = (*(float *)((int)&(param_2->Texel).v + local_160) -
                  *(float *)((int)&(param_2->Texel).v + iVar16)) * local_144;
      local_1ac._0_4_ =
           SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar16) + (float)Float2Int),0);
      fVar5 = (float)local_1ac._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar16);
      local_14c = (*(float *)((int)&(param_2->Texel).u + local_160) -
                  *(float *)((int)&(param_2->Texel).u + iVar16)) * local_144;
      local_144 = local_144 *
                  (*(float *)((int)&(param_2->Vector).x + local_160) -
                  *(float *)((int)&(param_2->Vector).x + iVar16));
      local_150 = local_148 * fVar5 + *(float *)((int)&(param_2->Texel).v + iVar16);
      local_154 = local_14c * fVar5 + *(float *)((int)&(param_2->Texel).u + iVar16);
      local_15c = fVar5 * local_144 + *(float *)((int)&(param_2->Vector).x + iVar16);
    }
    local_19c = (double)(local_134 + (float)Float2Int);
    dVar9 = local_19c;
    local_1a4 = (double)(local_15c + (float)Float2Int);
    dVar8 = local_1a4;
    local_19c._0_4_ = SUB84((double)(local_134 + (float)Float2Int),0);
    local_1a4._0_4_ = SUB84((double)(local_15c + (float)Float2Int),0);
    dVar13 = local_184;
    if (local_19c._0_4_ != local_1a4._0_4_) {
      fVar5 = UNITY / (local_15c - local_134);
      fVar6 = fVar5 * (local_154 - local_12c);
      if (local_19c._0_4_ < local_1a4._0_4_) {
        dVar13 = (double)local_19c._0_4_ - (double)local_134;
        iVar16 = local_19c._0_4_;
        fVar1 = local_12c;
        fVar2 = local_128;
      }
      else {
        dVar13 = (double)local_1a4._0_4_ - (double)local_15c;
        iVar16 = local_1a4._0_4_;
        local_1a4._0_4_ = local_19c._0_4_;
        fVar1 = local_154;
        fVar2 = local_150;
      }
      local_17c = (double)((local_150 - local_128) * fVar5);
      local_194 = Float2Int + (double)fVar1 + (double)fVar6 * dVar13;
      local_184 = dVar13 * local_17c + Float2Int + (double)fVar2;
      dVar10 = local_194;
      dVar13 = local_184;
      local_17c = local_17c + Float2Int;
      local_1a4._0_4_ = local_1a4._0_4_ - iVar16;
      dVar12 = local_17c;
      local_18c = (double)(fVar6 + (float)Float2Int);
      dVar11 = local_18c;
      iVar20 = local_194._0_4_;
      puVar22 = local_7d4 + iVar16;
      do {
        iVar16 = local_184._0_4_ >> 0x10;
        local_184._0_4_ = local_184._0_4_ + local_17c._0_4_;
        local_1a4._0_4_ = local_1a4._0_4_ + -1;
        *puVar22 = Translucency_Table[0]
                   [CONCAT22((short)(iVar20 >> 0x1f),
                             CONCAT11(*puVar22,Texture_Cache.Address[iVar16][iVar20 >> 0x10]))];
        iVar20 = iVar20 + local_18c._0_4_;
        puVar22 = puVar22 + 1;
        local_194 = dVar10;
        local_18c = dVar11;
        local_17c = dVar12;
      } while (local_1a4._0_4_ != 0);
    }
    local_184 = dVar13;
    local_134 = local_134 + local_11c;
    local_12c = local_12c + local_124;
    local_128 = local_128 + local_120;
    local_7d4 = local_7d4 + iVar3;
    local_1b4._0_4_ = local_1b4._0_4_ + 1;
    local_15c = local_15c + local_144;
    local_154 = local_154 + local_14c;
    local_150 = local_150 + local_148;
    local_1a4 = dVar8;
    local_19c = dVar9;
  } while( true );
}
