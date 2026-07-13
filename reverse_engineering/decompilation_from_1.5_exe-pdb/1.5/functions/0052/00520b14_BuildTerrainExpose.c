/*
 * Entry: 00520b14
 * Name: BuildTerrainExpose
 * Namespace: Global
 * Signature: void BuildTerrainExpose(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildTerrainExpose(CAMERA *param_1)

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
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  int iVar14;
  ushort *puVar15;
  int unaff_EBX;
  CAMERA *unaff_ESI;
  int unaff_EDI;
  int iVar16;
  VECTOR_3D *pVVar17;
  long local_68;
  long local_60;
  long local_58;
  long local_50;
  long local_48;
  long local_40;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  fVar13 = spriteZ;
  TrimToViewPort(unaff_ESI,&local_10,&local_28,&local_c,&local_18);
  iVar16 = local_c - local_10;
  for (local_8 = local_28; local_8 <= local_18; local_8 = local_8 + 1) {
    iVar14 = local_10;
    if (local_10 <= local_c) {
      do {
        AddVertex(unaff_EDI,unaff_EBX);
        iVar14 = iVar14 + 1;
      } while (iVar14 <= local_c);
    }
  }
  Transform_Terrain_Vertex_List();
  local_8 = local_28;
  if (local_28 < local_18) {
    iVar16 = (iVar16 + 1) * 0xc;
    local_24 = 0;
    local_28 = iVar16 + 0xc;
    pVVar17 = Vertex_Pool;
    do {
      local_14 = local_10;
      if (local_10 < local_c) {
        local_20 = local_24;
        local_1c = local_28;
        do {
          pVVar1 = (VECTOR_3D *)((int)&pVVar17->x + local_1c);
          pVVar2 = (VECTOR_3D *)((int)&pVVar17->x + local_20);
          pVVar3 = (VECTOR_3D *)((int)&pVVar17[1].x + local_20);
          iVar14 = OutsideViewport(unaff_ESI,pVVar2,pVVar3,pVVar1,pVVar1 + -1);
          if (iVar14 == 0) {
            puVar15 = GetTilePtr(local_14,local_8);
            lVar10 = MaterialColors[*puVar15 >> 0xc];
            spriteZ = fVar13;
            if (fVar13 < pVVar2->z) {
              spriteZ = pVVar2->z;
            }
            fVar11 = 1.0;
            fVar7 = fVar11;
            if (1.0 < pVVar2->z) {
              fVar7 = 1.0 / pVVar2->z;
            }
            fVar12 = (float)Float2Int;
            fVar6 = fVar11;
            if (1.0 < pVVar3->z) {
              fVar6 = 1.0 / pVVar3->z;
            }
            if (1.0 < pVVar1->z) {
              fVar11 = 1.0 / pVVar1->z;
            }
            fVar4 = pVVar1->x;
            local_40 = SUB84((double)(pVVar3->y * unaff_ESI->Const_y * fVar6 + unaff_ESI->Orig_y +
                                     fVar12),0);
            fVar5 = unaff_ESI->Const_x;
            local_48 = SUB84((double)(fVar6 * unaff_ESI->Const_x * pVVar3->x + unaff_ESI->Orig_x +
                                     fVar12),0);
            local_50 = SUB84((double)(pVVar2->y * unaff_ESI->Const_y * fVar7 + unaff_ESI->Orig_y +
                                     fVar12),0);
            fVar6 = unaff_ESI->Orig_x;
            local_58 = SUB84((double)(pVVar2->x * fVar7 * unaff_ESI->Const_x + unaff_ESI->Orig_x +
                                     fVar12),0);
            fVar7 = pVVar1->y;
            fVar8 = unaff_ESI->Const_y;
            fVar9 = unaff_ESI->Orig_y;
            Graphic_Line(unaff_ESI->Buffer,local_58,local_50,local_48,local_40,lVar10,SOLID_PIXELS);
            local_60 = SUB84((double)(fVar7 * fVar8 * fVar11 + fVar9 + fVar12),0);
            local_68 = SUB84((double)(fVar4 * fVar11 * fVar5 + fVar6 + fVar12),0);
            Graphic_Line(unaff_ESI->Buffer,local_48,local_40,local_68,local_60,lVar10,SOLID_PIXELS);
            pVVar17 = Vertex_Pool;
          }
          local_14 = local_14 + 1;
          local_1c = local_1c + 0xc;
          local_20 = local_20 + 0xc;
        } while (local_14 < local_c);
      }
      local_8 = local_8 + 1;
      local_24 = local_24 + iVar16;
      local_28 = local_28 + iVar16;
    } while (local_8 < local_18);
  }
  spriteZ = fVar13;
  return;
}
