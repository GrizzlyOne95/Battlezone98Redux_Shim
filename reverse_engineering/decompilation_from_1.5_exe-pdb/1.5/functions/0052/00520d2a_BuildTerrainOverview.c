/*
 * Entry: 00520d2a
 * Name: BuildTerrainOverview
 * Namespace: Global
 * Signature: void BuildTerrainOverview(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildTerrainOverview(CAMERA *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  byte *pbVar14;
  uint uVar15;
  ushort *puVar16;
  int unaff_EBX;
  int iVar17;
  CAMERA *unaff_ESI;
  int unaff_EDI;
  int iVar18;
  VECTOR_3D *pVVar19;
  long local_70;
  long local_68;
  long local_60;
  long local_58;
  long local_50;
  long local_48;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  fVar12 = spriteZ;
  TrimToViewPort(unaff_ESI,&local_18,&local_14,&local_10,&local_24);
  local_18 = local_18 >> 1;
  iVar13 = local_10 + 1 >> 1;
  iVar18 = iVar13 - local_18;
  iVar17 = local_24 + 1 >> 1;
  local_c = local_14 >> 1;
  local_14 = local_c;
  local_10 = iVar13;
  local_24 = iVar17;
  for (; local_c <= iVar17; local_c = local_c + 1) {
    local_8 = local_18;
    if (local_18 <= iVar13) {
      do {
        AddVertex(unaff_EDI,unaff_EBX);
        local_8 = local_8 + 1;
        iVar13 = local_10;
      } while (local_8 <= local_10);
    }
  }
  Transform_Terrain_Vertex_List();
  local_c = local_14;
  if (local_14 < iVar17) {
    iVar13 = (iVar18 + 1) * 0xc;
    local_28 = 0;
    local_2c = iVar13 + 0xc;
    pVVar19 = Vertex_Pool;
    do {
      local_8 = local_18;
      if (local_18 < local_10) {
        local_20 = local_18 * 2 + 1;
        local_1c = local_28;
        local_14 = local_2c;
        do {
          pVVar1 = (VECTOR_3D *)((int)&pVVar19->x + local_14);
          pVVar2 = (VECTOR_3D *)((int)&pVVar19->x + local_1c);
          pVVar3 = (VECTOR_3D *)((int)&pVVar19[1].x + local_1c);
          iVar17 = OutsideViewportTB(unaff_ESI,pVVar2,pVVar3,pVVar1,pVVar1 + -1);
          if ((iVar17 == 0) &&
             (iVar17 = OutsideViewport(unaff_ESI,pVVar2,pVVar3,pVVar1,pVVar1 + -1), iVar17 == 0)) {
            pbVar14 = GetNormalPtr(unaff_EDI,unaff_EBX);
            uVar15 = ((uint)*pbVar14 * 0x1f) / 0xff;
            puVar16 = GetTilePtr(local_8 * 2,local_c * 2);
            if ((uint)(*puVar16 >> 0xc) == lavaMat) {
              iVar17 = LavaColors[uVar15];
            }
            else {
              iVar17 = GreyColors[uVar15];
            }
            spriteZ = fVar12;
            if (fVar12 < pVVar2->z) {
              spriteZ = pVVar2->z;
            }
            fVar10 = 1.0;
            fVar7 = fVar10;
            if (1.0 < pVVar2->z) {
              fVar7 = 1.0 / pVVar2->z;
            }
            fVar11 = (float)Float2Int;
            fVar6 = fVar10;
            if (1.0 < pVVar3->z) {
              fVar6 = 1.0 / pVVar3->z;
            }
            if (1.0 < pVVar1->z) {
              fVar10 = 1.0 / pVVar1->z;
            }
            fVar4 = unaff_ESI->Const_x;
            fVar5 = pVVar1->x;
            local_48 = SUB84((double)(fVar6 * pVVar3->y * unaff_ESI->Const_y + unaff_ESI->Orig_y +
                                     fVar11),0);
            local_50 = SUB84((double)(unaff_ESI->Const_x * fVar6 * pVVar3->x + unaff_ESI->Orig_x +
                                     fVar11),0);
            local_58 = SUB84((double)(pVVar2->y * fVar7 * unaff_ESI->Const_y + unaff_ESI->Orig_y +
                                     fVar11),0);
            fVar6 = unaff_ESI->Orig_x;
            local_60 = SUB84((double)(pVVar2->x * unaff_ESI->Const_x * fVar7 + unaff_ESI->Orig_x +
                                     fVar11),0);
            fVar7 = pVVar1->y;
            fVar8 = unaff_ESI->Const_y;
            fVar9 = unaff_ESI->Orig_y;
            Graphic_Line(unaff_ESI->Buffer,local_60,local_58,local_50,local_48,iVar17,SOLID_PIXELS);
            local_68 = SUB84((double)(fVar10 * fVar7 * fVar8 + fVar9 + fVar11),0);
            local_70 = SUB84((double)(fVar4 * fVar5 * fVar10 + fVar6 + fVar11),0);
            Graphic_Line(unaff_ESI->Buffer,local_50,local_48,local_70,local_68,iVar17,SOLID_PIXELS);
            pVVar19 = Vertex_Pool;
          }
          local_8 = local_8 + 1;
          local_14 = local_14 + 0xc;
          local_1c = local_1c + 0xc;
          local_20 = local_20 + 2;
          iVar17 = local_24;
        } while (local_8 < local_10);
      }
      local_c = local_c + 1;
      local_28 = local_28 + iVar13;
      local_2c = local_2c + iVar13;
    } while (local_c < iVar17);
  }
  spriteZ = fVar12;
  return;
}
