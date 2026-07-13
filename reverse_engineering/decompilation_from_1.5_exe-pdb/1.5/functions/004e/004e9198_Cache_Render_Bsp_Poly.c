/*
 * Entry: 004e9198
 * Name: Cache_Render_Bsp_Poly
 * Namespace: Global
 * Signature: void Cache_Render_Bsp_Poly(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Render_Bsp_Poly(BSP_POLYGON *param_1)

{
  POINT_3D *pPVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  int in_EAX;
  TEXTURE *pTVar5;
  long lVar6;
  POINT_3D *pPVar7;
  float *pfVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  long unaff_EDI;
  uint uVar12;
  VECTOR_3D *pVVar13;
  POINT_3D local_310;
  VECTOR_3D local_2f8 [62];
  undefined8 local_10;
  uint local_8;
  
  if (*(char *)(in_EAX + 1) == '\0') {
    return;
  }
  if (((*(_OBJ76 **)(in_EAX + 4))->flags & 1) != 0) {
    return;
  }
  local_10 = (ulonglong)CONCAT14(*(undefined1 *)(in_EAX + 2),(int)local_10);
  local_8 = (uint)*(byte *)(in_EAX + 3);
  if (((byte)LODInfo.flags & 1) != 0) {
    local_8 = local_8 & 0xffffffeb;
  }
  if ((local_8 & 4) != 0) {
    if (*(char **)(in_EAX + 8) != (char *)0x0) {
      pTVar5 = Texture_Get(*(_OBJ76 **)(in_EAX + 4),*(char **)(in_EAX + 8));
      local_10 = CONCAT44(pTVar5,(int)local_10);
      if (pTVar5 != (TEXTURE *)0x0) {
        local_8 = local_8 | 0x11;
        goto LAB_004e91fd;
      }
    }
    local_8 = local_8 & 0xffffffeb;
  }
LAB_004e91fd:
  uVar11 = (uint)*(byte *)(in_EAX + 1);
  if (((byte)LODInfo.flags & 2) == 0) {
    pfVar8 = (float *)(&stack0xfffffcd8 + uVar11 * 0x18);
    piVar10 = (int *)(in_EAX + 0x30);
    for (; 0 < (int)uVar11; uVar11 = uVar11 - 1) {
      iVar9 = piVar10[1];
      pfVar8[3] = (float)piVar10[2];
      pfVar8[4] = (float)piVar10[3];
      iVar3 = *piVar10;
      pfVar8[5] = Luma_Base_Entry[iVar9];
      pVVar13 = Vertex_Pool + iVar3;
      *pfVar8 = pVVar13->x;
      pfVar2 = pfVar8 + 2;
      pfVar8[1] = pVVar13->y;
      piVar10 = piVar10 + 4;
      pfVar8 = pfVar8 + -6;
      *pfVar2 = pVVar13->z;
    }
    if (useD3D == 0) {
      __Camera_Software_Draw_polygon__
                (Local_Camera,&local_310,(uint)*(byte *)(in_EAX + 1),local_10._4_4_,local_8);
    }
    else {
      __Camera_Hardware_Draw_polygon__
                (Local_Camera,&local_310,(uint)*(byte *)(in_EAX + 1),local_10._4_4_,local_8);
    }
  }
  else {
    piVar10 = (int *)(in_EAX + 0x30);
    local_10._0_4_ =
         SUB84((double)(Luma_Base_Entry[*(int *)(in_EAX + 0x34)] * 31.0 + (float)Float2Int),0);
    local_10 = (ulonglong)
               CONCAT14((&DAT_00d20480)[(uint)*(byte *)(in_EAX + 2) + (int)local_10 * -0x100],
                        (int)local_10);
    if (uVar11 != 0) {
      pfVar8 = &local_310.Vector.z;
      uVar12 = uVar11;
      do {
        pVVar13 = Vertex_Pool + *piVar10;
        piVar10 = piVar10 + 4;
        ((VECTOR_3D *)(pfVar8 + -2))->x = pVVar13->x;
        pfVar8[-1] = pVVar13->y;
        *pfVar8 = pVVar13->z;
        pfVar8 = pfVar8 + 6;
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
    }
    lVar6 = __Clip_3D_Polygon(Local_Camera,&local_310,&local_310,uVar11,1);
    local_8 = lVar6;
    if (2 < lVar6) {
      pPVar1 = &local_310 + lVar6;
      (pPVar1->Vector).x = local_310.Vector.x;
      local_2f8[lVar6 * 2 + -2].y = local_310.Vector.y;
      fVar4 = (float)(int)local_8;
      if (1 < lVar6) {
        iVar9 = lVar6 + -1;
        pPVar7 = &local_310;
        do {
          iVar9 = iVar9 + -1;
          (pPVar1->Vector).x = (pPVar1->Vector).x + pPVar7[1].Vector.x;
          local_2f8[lVar6 * 2 + -2].y = pPVar7[1].Vector.y + local_2f8[lVar6 * 2 + -2].y;
          pPVar7 = pPVar7 + 1;
        } while (iVar9 != 0);
      }
      pVVar13 = (VECTOR_3D *)local_10._4_4_;
      (pPVar1->Vector).x = (pPVar1->Vector).x * (1.0 / fVar4);
      local_2f8[lVar6 * 2 + -2].y = (1.0 / fVar4) * local_2f8[lVar6 * 2 + -2].y;
      Screen_Draw_Pixel(Local_Camera,pVVar13,unaff_EDI);
      if (LODInfo.subdivideDepth != 0) {
        if (1 < lVar6) {
          pVVar13 = local_2f8;
          iVar9 = lVar6 + -1;
          do {
            SubdivideTriangle(pVVar13 + -2,pVVar13,&pPVar1->Vector,local_10._4_4_,
                              LODInfo.subdivideDepth);
            pVVar13 = pVVar13 + 2;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
        SubdivideTriangle((VECTOR_3D *)(&stack0xfffffcd8 + lVar6 * 0x18),&local_310.Vector,
                          &pPVar1->Vector,local_10._4_4_,LODInfo.subdivideDepth);
      }
    }
  }
  return;
}
