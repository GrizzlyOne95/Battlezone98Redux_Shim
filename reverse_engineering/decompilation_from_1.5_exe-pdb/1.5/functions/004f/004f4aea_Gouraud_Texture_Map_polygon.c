/*
 * Entry: 004f4aea
 * Name: Gouraud_Texture_Map_polygon
 * Namespace: Global
 * Signature: void Gouraud_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Gouraud_Texture_Map_polygon
          (_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  POLYGON_SKIN PVar12;
  char **ppcVar13;
  int iVar14;
  int iVar15;
  char *pcVar16;
  int iVar17;
  char *pcVar18;
  char *pcVar19;
  uchar *puVar20;
  int local_6e4;
  int local_6dc;
  int local_6d4;
  int local_6cc;
  int local_6bc;
  int local_6b4;
  int local_694;
  int local_68c;
  uchar *local_67c;
  int local_674;
  float local_670;
  float local_668;
  float local_664;
  float local_65c;
  float local_658;
  float local_654;
  int local_644;
  float local_640;
  float local_638;
  float local_634;
  float local_62c;
  float local_628;
  float local_624;
  POLYGON_SKIN local_618 [6];
  POLYGON_SKIN aPStack_600 [180];
  POLYGON_SKIN aPStack_330 [6];
  int aiStack_318 [193];
  undefined1 *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  if (Texture_Cache.Name != (TEXTURE *)param_4.Color) {
    Texture_Cache.Name = param_4.Texture;
    ppcVar13 = Texture_Cache.Address;
    pcVar18 = (char *)(param_4.Color + 8);
    iVar4 = *(int *)param_4.Texture;
    iVar14 = (param_4.Texture)->height;
    pcVar19 = pcVar18 + iVar4;
    pcVar16 = pcVar18 + iVar4 * 2;
    iVar4 = iVar4 * 3;
    iVar17 = iVar14 + 3;
    Texture_Cache.Padding[0] = pcVar18;
    Texture_Cache.Padding[1] = pcVar18;
    Texture_Cache.Padding[2] = pcVar18;
    Texture_Cache.Padding[3] = pcVar18;
    do {
      *ppcVar13 = pcVar18;
      ppcVar13[1] = pcVar19;
      ppcVar13[2] = pcVar16;
      pcVar18 = pcVar18 + iVar4;
      pcVar19 = pcVar19 + iVar4;
      pcVar16 = pcVar16 + iVar4;
      ppcVar13 = ppcVar13 + 3;
      bVar5 = 2 < iVar17;
      iVar17 = iVar17 + -3;
    } while (bVar5);
    pcVar18 = Texture_Cache.Padding[iVar14 + 3];
    Texture_Cache.Address[iVar14] = pcVar18;
    Texture_Cache.Address[iVar14 + 1] = pcVar18;
    Texture_Cache.Address[iVar14 + 2] = pcVar18;
    Texture_Cache.Address[iVar14 + 3] = pcVar18;
  }
  iVar14 = 100000;
  iVar4._0_2_ = *(short *)param_4;
  iVar4._2_2_ = *(short *)((int)param_4 + 2);
  fVar7 = ((float)(param_4.Texture)->height - UNITY) * UV_SCALE;
  fVar6 = ((float)iVar4 - UNITY) * UV_SCALE;
  PVar12.Color = 0;
  do {
    local_618[0] = PVar12;
    fVar1 = *(float *)((int)&(param_2->Vector).y + (int)local_618[0].Texture);
    fVar8 = (float)Float2Int;
    fVar2 = *(float *)((int)&(param_2->Texel).u + (int)local_618[0].Texture);
    fVar3 = *(float *)((int)&(param_2->Texel).v + (int)local_618[0].Texture);
    ((POLYGON_SKIN *)((int)aPStack_330 + (int)local_618[0].Texture))->Texture =
         (TEXTURE *)local_618[0];
    ((POLYGON_SKIN *)((int)aPStack_600 + (int)local_618[0].Texture))->Texture =
         (TEXTURE *)local_618[0];
    *(float *)((int)&(param_2->Texel).u + (int)local_618[0].Texture) = fVar2 * fVar6;
    local_6dc = SUB84((double)(fVar1 + fVar8),0);
    *(float *)((int)&(param_2->Texel).v + (int)local_618[0].Texture) = fVar3 * fVar7;
    PVar12.Texture = (TEXTURE *)(local_618[0].Color + 0x18);
    if (local_6dc <= iVar14) {
      iVar14 = local_6dc;
      param_4.Texture = PVar12.Texture;
    }
  } while (PVar12.Color != param_3 * 0x18);
  iVar17 = param_4.Color + -0x18;
  *(undefined4 *)((int)aPStack_330 + (int)PVar12.Texture) = 0;
  iVar4 = param_1->Width;
  local_67c = param_1->Buffer + ((param_1->Pane).y0 + iVar14) * iVar4 + (param_1->Pane).x0;
  local_6e4 = SUB84((double)(*(float *)((int)&(param_4.Texture)->width + (int)&param_2[-1].Vector.y)
                            + (float)Float2Int),0);
  local_674 = iVar17;
  local_644 = iVar17;
  do {
    local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + local_644) + (float)Float2Int)
                      ,0);
    if (local_6dc <= local_6e4) {
      do {
        iVar14 = local_644;
        local_644 = *(int *)((int)aiStack_318 + iVar14);
        if (local_644 == iVar17) {
          return;
        }
        local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + local_644) +
                                  (float)Float2Int),0);
      } while (local_6dc <= local_6e4);
      fVar6 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_644) -
                      *(float *)((int)&(param_2->Vector).y + iVar14));
      local_628 = (*(float *)((int)&(param_2->Texel).v + local_644) -
                  *(float *)((int)&(param_2->Texel).v + iVar14)) * fVar6;
      local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar14) + (float)Float2Int),
                        0);
      fVar7 = (float)local_6dc - *(float *)((int)&(param_2->Vector).y + iVar14);
      local_62c = (*(float *)((int)&(param_2->Texel).u + local_644) -
                  *(float *)((int)&(param_2->Texel).u + iVar14)) * fVar6;
      local_624 = fVar6 * (*(float *)((int)&(param_2->Vector).x + local_644) -
                          *(float *)((int)&(param_2->Vector).x + iVar14));
      local_634 = local_628 * fVar7 + *(float *)((int)&(param_2->Texel).v + iVar14);
      local_638 = local_62c * fVar7 + *(float *)((int)&(param_2->Texel).u + iVar14);
      local_640 = fVar7 * local_624 + *(float *)((int)&(param_2->Vector).x + iVar14);
    }
    local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + local_674) + (float)Float2Int)
                      ,0);
    if (local_6dc <= local_6e4) {
      do {
        iVar14 = local_674;
        local_674 = *(int *)((int)local_618 + iVar14);
        local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + local_674) +
                                  (float)Float2Int),0);
      } while (local_6dc <= local_6e4);
      fVar6 = UNITY / (*(float *)((int)&(param_2->Vector).y + local_674) -
                      *(float *)((int)&(param_2->Vector).y + iVar14));
      local_658 = (*(float *)((int)&(param_2->Texel).v + local_674) -
                  *(float *)((int)&(param_2->Texel).v + iVar14)) * fVar6;
      local_6dc = SUB84((double)(*(float *)((int)&(param_2->Vector).y + iVar14) + (float)Float2Int),
                        0);
      fVar7 = (float)local_6dc - *(float *)((int)&(param_2->Vector).y + iVar14);
      local_65c = (*(float *)((int)&(param_2->Texel).u + local_674) -
                  *(float *)((int)&(param_2->Texel).u + iVar14)) * fVar6;
      local_654 = fVar6 * (*(float *)((int)&(param_2->Vector).x + local_674) -
                          *(float *)((int)&(param_2->Vector).x + iVar14));
      local_664 = local_658 * fVar7 + *(float *)((int)&(param_2->Texel).v + iVar14);
      local_668 = local_65c * fVar7 + *(float *)((int)&(param_2->Texel).u + iVar14);
      local_670 = fVar7 * local_654 + *(float *)((int)&(param_2->Vector).x + iVar14);
    }
    local_6cc = SUB84((double)(local_640 + (float)Float2Int),0);
    local_6d4 = SUB84((double)(local_670 + (float)Float2Int),0);
    if (local_6cc != local_6d4) {
      fVar6 = UNITY / (local_670 - local_640);
      fVar7 = fVar6 * (local_668 - local_638);
      if (local_6cc < local_6d4) {
        dVar9 = (double)local_6cc - (double)local_640;
        iVar14 = local_6cc;
        fVar1 = local_638;
        fVar2 = local_634;
      }
      else {
        dVar9 = (double)local_6d4 - (double)local_670;
        iVar14 = local_6d4;
        local_6d4 = local_6cc;
        fVar1 = local_668;
        fVar2 = local_664;
      }
      dVar10 = (double)((local_664 - local_634) * fVar6);
      fVar6 = (float)Float2Int;
      dVar11 = dVar10 + Float2Int;
      local_6d4 = local_6d4 - iVar14;
      local_68c = SUB84(dVar9 * dVar10 + Float2Int + (double)fVar2,0);
      puVar20 = local_67c + iVar14;
      local_694 = SUB84(Float2Int + (double)fVar1 + (double)fVar7 * dVar9,0);
      do {
        iVar14 = local_68c >> 0x10;
        local_6b4 = SUB84(dVar11,0);
        iVar15 = local_694 >> 0x10;
        local_68c = local_68c + local_6b4;
        local_6bc = SUB84((double)(fVar7 + fVar6),0);
        local_694 = local_694 + local_6bc;
        *puVar20 = Texture_Cache.Address[iVar14][iVar15];
        puVar20 = puVar20 + 1;
        local_6d4 = local_6d4 + -1;
      } while (local_6d4 != 0);
    }
    local_664 = local_664 + local_658;
    local_668 = local_668 + local_65c;
    local_670 = local_670 + local_654;
    local_640 = local_640 + local_624;
    local_638 = local_638 + local_62c;
    local_634 = local_634 + local_628;
    local_67c = local_67c + iVar4;
    local_6e4 = local_6e4 + 1;
  } while( true );
}
