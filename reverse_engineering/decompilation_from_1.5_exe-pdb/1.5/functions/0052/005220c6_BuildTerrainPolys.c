/*
 * Entry: 005220c6
 * Name: BuildTerrainPolys
 * Namespace: Global
 * Signature: void BuildTerrainPolys(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildTerrainPolys(CAMERA *param_1)

{
  ushort uVar1;
  DWORD DVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  tagLIGHTING *ptVar6;
  tagMIX2UV *unaff_ESI;
  uint uVar7;
  VECTOR_3D *pVVar8;
  VECTOR_3D *pVVar9;
  tagLIGHTING unaff_EDI;
  tagLIGHTING *ptVar10;
  VECTOR_3D *pVVar11;
  VECTOR_3D *pVVar12;
  tagLIGHTING tVar13;
  tagLIGHTING tVar14;
  tagLIGHTING tVar15;
  tagLIGHTING tVar16;
  VECTOR_3D *local_58;
  VECTOR_3D *local_54;
  tagLIGHTING *local_50;
  tagLIGHTING *local_4c;
  int local_48;
  VECTOR_3D *local_44;
  VECTOR_3D *local_40;
  VECTOR_3D *local_3c;
  VECTOR_3D *local_38;
  uint local_34;
  tagLIGHTING *local_30;
  VECTOR_3D *local_2c;
  int local_28;
  tagLIGHTING *local_24;
  uint local_20;
  tagLIGHTING local_1c;
  int local_18;
  float local_14;
  VECTOR_3D *local_10;
  uint local_c;
  tagLIGHTING *local_8;
  
  if ((TerrainTextured == 0) || (TileFileCount == 0)) {
    solidPoly = 1;
  }
  else {
    solidPoly = 0;
    flatROP = 0x109;
  }
  TrimToViewPort(param_1,(int *)&local_34,(int *)&local_50,&local_28,&local_18);
  iVar3 = local_28;
  ptVar6 = local_50;
  iVar5 = (local_28 - local_34) + 1;
  local_8 = local_50;
  uVar7 = local_34;
  if ((int)local_50 <= local_18) {
    do {
      while (local_c = uVar7, (int)local_c <= iVar3) {
        AddVertex((int)unaff_EDI,(int)unaff_ESI);
        uVar7 = local_c + 1;
      }
      local_8 = (tagLIGHTING *)&(local_8->l).fogginess;
      uVar7 = local_34;
    } while ((int)local_8 <= local_18);
  }
  Transform_Terrain_Vertex_List();
  ptVar10 = Quadtree_Cell_Pool;
  local_54 = Quadtree_Cell_Pool;
  (*Light_Terrain_Vertex_List)(local_34,(long)ptVar6,iVar3,local_18,Vertex_Pool,Quadtree_Cell_Pool);
  if (-1 < waveMat) {
    DVar2 = timeGetTime();
    if (0x32 < DVar2 - lastWaveTime) {
      lastWaveIndex = lastWaveIndex + 1U & 0x7f;
      lastWaveTime = timeGetTime();
    }
    faceMask = 3;
  }
  iVar3 = waveMat;
  local_58 = (VECTOR_3D *)((int)Quadtree_Cell_Pool + ((local_18 - (int)ptVar6) + 1) * iVar5 * 4);
  local_10 = Vertex_Pool;
  if ((waveEnable == 0) || (waveMat < 0)) {
    pVVar9 = local_58;
    for (local_8 = local_50; uVar7 = local_34, (int)local_8 <= local_18;
        local_8 = (tagLIGHTING *)&(local_8->l).fogginess) {
      for (; (int)uVar7 <= local_28; uVar7 = uVar7 + 1) {
        puVar4 = GetTilePtr(uVar7,(int)local_8);
        *(ushort *)&pVVar9->x = *puVar4;
        pVVar9 = (VECTOR_3D *)((int)&pVVar9->x + 2);
      }
    }
  }
  else {
    pVVar9 = local_58;
    for (local_8 = local_50; (int)local_8 <= local_18; local_8 = (tagLIGHTING *)((int)local_8 + 1))
    {
      local_c = local_34;
      if ((int)local_34 <= local_28) {
        local_4c = (tagLIGHTING *)(local_34 * 0x20 + lastWaveIndex);
        do {
          puVar4 = GetTilePtr(local_c,(int)local_8);
          uVar1 = *puVar4;
          *(ushort *)&pVVar9->x = uVar1;
          if ((iVar3 == (uVar1 >> 8 & 0xf)) && (iVar3 == (uint)(uVar1 >> 0xc))) {
            local_10->y = WaveTable[(uint)local_4c & 0x7f] + local_10->y;
          }
          local_10 = local_10 + 1;
          local_4c = (tagLIGHTING *)((int)local_4c + 0x20);
          pVVar9 = (VECTOR_3D *)((int)&pVVar9->x + 2);
          local_c = local_c + 1;
        } while ((int)local_c <= local_28);
      }
    }
  }
  local_10 = Vertex_Pool;
  pVVar9 = Vertex_Pool + iVar5;
  ptVar6 = (tagLIGHTING *)((int)ptVar10 + iVar5 * 4);
  local_8 = local_50;
  local_2c = local_58;
  do {
    if (local_18 <= (int)local_8) {
      return;
    }
    local_c = local_34;
    if ((int)local_34 < local_28) {
      local_4c = ptVar10 + 2;
      local_50 = ptVar6 + 2;
      local_44 = pVVar9 + 1;
      local_40 = local_10 + 1;
      local_48 = local_34 + 2;
      pVVar8 = pVVar9;
      local_30 = ptVar10;
      local_24 = ptVar6;
      do {
        pVVar12 = local_10;
        local_24 = local_24 + 1;
        local_30 = local_30 + 1;
        pVVar11 = local_10 + 1;
        local_40 = local_40 + 1;
        local_44 = local_44 + 1;
        pVVar9 = pVVar8 + 1;
        local_3c = local_10;
        local_38 = pVVar8;
        local_10 = pVVar11;
        iVar3 = OutsideViewport(param_1,pVVar12,pVVar11,pVVar9,pVVar8);
        if ((iVar3 == 0) && (local_20 = FacesIn(local_3c,local_10,pVVar9,local_38), local_20 != 0))
        {
          puVar4 = GetZonePtr(local_c,(int)local_8);
          if ((local_20 == 3) &&
             (((((*puVar4 & 0x8000) != 0 && (3 < faceMask)) &&
               (local_20 = 7, (*puVar4 & 0x4000) != 0)) &&
              ((local_48 <= local_28 && (7 < faceMask)))))) {
            local_58 = local_40;
            local_54 = local_44;
            iVar3 = FacesIn(local_10,local_40,local_44,pVVar9);
            if (iVar3 == 3) {
              local_20 = 0xf;
            }
          }
          local_14 = local_3c->z;
          if (((byte)D3IniFlags & 1) == 0) {
            if (((uint)(local_14 - local_10->z) & 0x80000000) != 0) {
              local_14 = local_10->z;
            }
            if (((uint)(local_14 - pVVar8[1].z) & 0x80000000) != 0) {
              local_14 = pVVar8[1].z;
            }
            if (((uint)(local_14 - local_38->z) & 0x80000000) != 0) {
              local_14 = local_38->z;
            }
            if ((local_20 & 8) != 0) {
              if (((uint)(local_14 - local_58->z) & 0x80000000) != 0) {
                local_14 = local_58->z;
              }
              if (((uint)(local_14 - local_54->z) & 0x80000000) != 0) {
                local_14 = local_54->z;
              }
            }
          }
          if ((TerrainView.Flat_Range < local_14) || (solidPoly != 0)) {
            uVar1 = *(ushort *)&local_2c->x;
            local_1c.luma = 0.0;
          }
          else {
            uVar1 = *(ushort *)&local_2c->x;
            pre_maxM = uVar1 >> 8 & 0xf;
            pre_cap = uVar1 >> 7 & 1;
            pre_mix = uVar1 >> 4 & 0xf;
            pre_var = uVar1 & 3;
            local_1c = (tagLIGHTING)(mix2UV[pre_mix][(uint)local_8 & 1] + (local_c & 1));
          }
          pre_minM = (int)(uVar1 >> 0xc);
          if ((local_20 & 8) == 0) {
            if ((local_20 & 4) == 0) {
              if ((local_20 & 1) != 0) {
                AddTerrainPoly(local_c,(int)local_8,1,local_14,local_10,pVVar9,(VECTOR_3D *)0x0,
                               (VECTOR_3D *)*ptVar10,*local_30,*local_24,(tagLIGHTING)0x0,local_1c,
                               (tagMIX2UV *)unaff_EDI);
              }
              if ((local_20 & 2) == 0) goto LAB_005225f5;
              tVar16.luma = 0.0;
              tVar15 = *ptVar6;
              tVar14 = *local_24;
              tVar13 = *ptVar10;
              pVVar12 = (VECTOR_3D *)0x0;
              iVar3 = 2;
              pVVar8 = pVVar9;
              pVVar11 = local_38;
            }
            else {
              tVar16 = *ptVar6;
              tVar15 = *local_24;
              tVar14 = *local_30;
              tVar13 = *ptVar10;
              iVar3 = 3;
              pVVar8 = local_10;
              pVVar11 = pVVar9;
              pVVar12 = local_38;
            }
            AddTerrainPoly(local_c,(int)local_8,iVar3,local_14,pVVar8,pVVar11,pVVar12,
                           (VECTOR_3D *)tVar13,tVar14,tVar15,tVar16,local_1c,(tagMIX2UV *)unaff_EDI)
            ;
          }
          else {
            AddTerrainSlab(local_c,(int)local_8,(int)local_14,(float)local_3c,pVVar9,local_38,
                           local_58,local_54,(VECTOR_3D *)*ptVar10,(VECTOR_3D *)*local_30,*local_24,
                           *ptVar6,*local_4c,*local_50,local_1c,unaff_EDI,unaff_ESI);
            local_c = local_c + 1;
            local_48 = local_48 + 1;
            local_10 = local_10 + 1;
            local_40 = local_40 + 1;
            local_44 = local_44 + 1;
            pVVar9 = pVVar8 + 2;
            local_4c = local_4c + 1;
            local_30 = local_30 + 1;
            local_50 = local_50 + 1;
            local_24 = local_24 + 1;
            ptVar10 = ptVar10 + 1;
            ptVar6 = ptVar6 + 1;
            local_2c = (VECTOR_3D *)((int)&local_2c->x + 2);
          }
        }
LAB_005225f5:
        local_c = local_c + 1;
        local_48 = local_48 + 1;
        local_2c = (VECTOR_3D *)((int)&local_2c->x + 2);
        local_4c = local_4c + 1;
        local_50 = local_50 + 1;
        ptVar10 = ptVar10 + 1;
        ptVar6 = ptVar6 + 1;
        pVVar8 = pVVar9;
      } while ((int)local_c < local_28);
    }
    local_8 = (tagLIGHTING *)((int)local_8 + 1);
    local_10 = local_10 + 1;
    pVVar9 = pVVar9 + 1;
    ptVar10 = ptVar10 + 1;
    ptVar6 = ptVar6 + 1;
    local_2c = (VECTOR_3D *)((int)&local_2c->x + 2);
  } while( true );
}
