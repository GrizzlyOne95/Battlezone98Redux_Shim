/*
 * Entry: 004e8aac
 * Name: Draw_Pixel_Model
 * Namespace: Global
 * Signature: void Draw_Pixel_Model(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Draw_Pixel_Model(BSP_POLYGON *param_1)

{
  double dVar1;
  int in_EAX;
  long lVar2;
  POINT_3D *pPVar3;
  int iVar4;
  long unaff_EBX;
  VECTOR_3D *pVVar5;
  VECTOR_3D *pVVar6;
  POINT_3D local_31c;
  VECTOR_3D local_304 [62];
  double local_1c;
  VECTOR_3D local_14;
  int local_8;
  
  lVar2 = __Clip_3D_Polygon(Local_Camera,&local_31c,(POINT_3D *)(in_EAX + 0x30),
                            (uint)*(byte *)(in_EAX + 1),1);
  local_8 = lVar2;
  if (2 < lVar2) {
    local_1c = (double)(*(float *)(in_EAX + 0x44) * 31.0 + (float)Float2Int);
    dVar1 = local_1c;
    pVVar5 = (VECTOR_3D *)
             (uint)(byte)(&DAT_00d20480)[(uint)*(byte *)(in_EAX + 2) + local_1c._0_4_ * -0x100];
    if (1 < lVar2) {
      iVar4 = lVar2 + -1;
      pPVar3 = &local_31c;
      do {
        iVar4 = iVar4 + -1;
        local_31c.Vector.x = local_31c.Vector.x + pPVar3[1].Vector.x;
        local_31c.Vector.y = pPVar3[1].Vector.y + local_31c.Vector.y;
        pPVar3 = pPVar3 + 1;
      } while (iVar4 != 0);
    }
    local_14.x = (1.0 / (float)lVar2) * local_31c.Vector.x;
    local_14.y = local_31c.Vector.y * (1.0 / (float)lVar2);
    local_1c = dVar1;
    Screen_Draw_Pixel(Local_Camera,pVVar5,unaff_EBX);
    if (LODInfo.subdivideDepth != 0) {
      if (1 < lVar2) {
        local_8 = lVar2 + -1;
        pVVar6 = local_304;
        do {
          SubdivideTriangle(pVVar6 + -2,pVVar6,&local_14,(int)pVVar5,LODInfo.subdivideDepth);
          pVVar6 = pVVar6 + 2;
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
      SubdivideTriangle((VECTOR_3D *)(&stack0xfffffccc + lVar2 * 0x18),&local_31c.Vector,&local_14,
                        (int)pVVar5,LODInfo.subdivideDepth);
    }
  }
  return;
}
