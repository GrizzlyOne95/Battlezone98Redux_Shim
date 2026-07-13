/*
 * Entry: 00520881
 * Name: BuildTerrainWireFrame
 * Namespace: Global
 * Signature: void BuildTerrainWireFrame(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildTerrainWireFrame(CAMERA *param_1)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  ushort *puVar11;
  int unaff_EBX;
  CAMERA *unaff_ESI;
  int unaff_EDI;
  int iVar12;
  VECTOR_3D *pVVar13;
  long local_6c;
  long local_64;
  long local_5c;
  long local_54;
  long local_4c;
  long local_44;
  VECTOR_3D *local_38;
  VECTOR_3D *local_34;
  float local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  long local_10;
  VECTOR_3D *local_c;
  int local_8;
  
  local_30 = spriteZ;
  local_10 = 0xf;
  TrimToViewPort(unaff_ESI,&local_1c,(int *)&local_38,&local_14,&local_18);
  iVar12 = local_14 - local_1c;
  local_c = local_38;
  if ((int)local_38 <= local_18) {
    do {
      for (local_8 = local_1c; local_8 <= local_14; local_8 = local_8 + 1) {
        AddVertex(unaff_EDI,unaff_EBX);
      }
      local_c = (VECTOR_3D *)((int)&local_c->x + 1);
    } while ((int)local_c <= local_18);
  }
  Transform_Terrain_Vertex_List();
  local_c = local_38;
  if ((int)local_38 < local_18) {
    iVar12 = (iVar12 + 1) * 0xc;
    local_28 = 0;
    local_2c = iVar12 + 0xc;
    pVVar13 = Vertex_Pool;
    do {
      local_8 = local_1c;
      if (local_1c < local_14) {
        local_24 = local_28;
        local_20 = local_2c;
        do {
          pVVar1 = (VECTOR_3D *)((int)&pVVar13->x + local_20);
          local_34 = (VECTOR_3D *)((int)&pVVar13->x + local_24);
          local_38 = (VECTOR_3D *)((int)&pVVar13[1].x + local_24);
          iVar10 = OutsideViewport(unaff_ESI,local_34,local_38,pVVar1,pVVar1 + -1);
          if ((iVar10 == 0) && (iVar10 = FacesIn(local_34,local_38,pVVar1,pVVar1 + -1), iVar10 != 0)
             ) {
            if (TerrainWireColor == 1) {
              puVar11 = GetZonePtr(local_8,(int)local_c);
              local_10 = WireFrameColors[((*puVar11 & 0xfff) * 0xff) / 0xfff];
            }
            else if (TerrainWireColor == 2) {
              puVar11 = GetTilePtr(local_8,(int)local_c);
              local_10 = MaterialColors[*puVar11 >> 0xc];
            }
            spriteZ = local_30;
            if (local_30 < local_34->z) {
              spriteZ = local_34->z;
            }
            fVar8 = 1.0;
            fVar5 = fVar8;
            if (1.0 < local_34->z) {
              fVar5 = 1.0 / local_34->z;
            }
            fVar9 = (float)Float2Int;
            fVar4 = fVar8;
            if (1.0 < local_38->z) {
              fVar4 = 1.0 / local_38->z;
            }
            if (1.0 < pVVar1->z) {
              fVar8 = 1.0 / pVVar1->z;
            }
            fVar2 = unaff_ESI->Const_x;
            fVar3 = pVVar1->x;
            local_44 = SUB84((double)(local_38->y * unaff_ESI->Const_y * fVar4 + unaff_ESI->Orig_y +
                                     fVar9),0);
            local_4c = SUB84((double)(unaff_ESI->Const_x * fVar4 * local_38->x + unaff_ESI->Orig_x +
                                     fVar9),0);
            fVar4 = unaff_ESI->Orig_x;
            local_54 = SUB84((double)(local_34->y * unaff_ESI->Const_y * fVar5 + unaff_ESI->Orig_y +
                                     fVar9),0);
            local_5c = SUB84((double)(local_34->x * unaff_ESI->Const_x * fVar5 + unaff_ESI->Orig_x +
                                     fVar9),0);
            fVar5 = pVVar1->y;
            fVar6 = unaff_ESI->Const_y;
            fVar7 = unaff_ESI->Orig_y;
            Graphic_Line(unaff_ESI->Buffer,local_5c,local_54,local_4c,local_44,local_10,SOLID_PIXELS
                        );
            local_64 = SUB84((double)(fVar5 * fVar6 * fVar8 + fVar7 + fVar9),0);
            local_6c = SUB84((double)(fVar2 * fVar3 * fVar8 + fVar4 + fVar9),0);
            Graphic_Line(unaff_ESI->Buffer,local_4c,local_44,local_6c,local_64,local_10,SOLID_PIXELS
                        );
            Graphic_Line(unaff_ESI->Buffer,local_6c,local_64,local_5c,local_54,local_10,SOLID_PIXELS
                        );
            pVVar13 = Vertex_Pool;
          }
          local_8 = local_8 + 1;
          local_20 = local_20 + 0xc;
          local_24 = local_24 + 0xc;
        } while (local_8 < local_14);
      }
      local_c = (VECTOR_3D *)((int)&local_c->x + 1);
      local_28 = local_28 + iVar12;
      local_2c = local_2c + iVar12;
    } while ((int)local_c < local_18);
  }
  spriteZ = local_30;
  return;
}
