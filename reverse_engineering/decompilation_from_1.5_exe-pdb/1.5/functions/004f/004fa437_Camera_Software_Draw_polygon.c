/*
 * Entry: 004fa437
 * Name: __Camera_Software_Draw_polygon__
 * Namespace: Global
 * Signature: void __Camera_Software_Draw_polygon__(CAMERA * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
__Camera_Software_Draw_polygon__
          (CAMERA *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4,long param_5)

{
  byte *pbVar1;
  uint uVar2;
  long lVar3;
  int unaff_EBX;
  POINT_3D local_304;
  VECTOR_3D local_2ec [62];
  
  uVar2 = param_5 & 0x1ff;
  if (param_3 != 1) {
    if (param_3 == 2) {
      local_304.Vector.x = (param_2->Vector).x;
      local_304.Vector.y = (param_2->Vector).y;
      local_304.Vector.z = (param_2->Vector).z;
      local_2ec[0].x = param_2[1].Vector.x;
      local_2ec[0].y = param_2[1].Vector.y;
      local_2ec[0].z = param_2[1].Vector.z;
      Camera_Draw_Line(param_1,&local_304.Vector,local_2ec,param_4.Color);
    }
    else {
      if ((param_5 & 4U) != 0) {
        if (param_4.Color == 0) {
          uVar2 = param_5 & 0x1fb;
        }
        if (((uVar2 & 4) != 0) && (((int)(param_4.Texture)->width | (param_4.Texture)->height) == 1)
           ) {
          pbVar1 = (byte *)(param_4.Color + 8);
          param_4.Color._1_3_ = 0;
          param_4.Color._0_1_ = *pbVar1;
          uVar2 = uVar2 & 0xfffffffb;
        }
      }
      lVar3 = (*Clip_3d_Poly_Vtltbl[uVar2])(param_1,&local_304,param_2,param_3,uVar2);
      if (lVar3 != 0) {
        Set_Rounding(unaff_EBX);
        Polygon_Counter = Polygon_Counter + 1;
        (*Draw_3d_Poly_Vtltbl[uVar2])(param_1->Buffer,&local_304,lVar3,param_4);
        Set_Rounding(unaff_EBX);
      }
    }
    return;
  }
  Camera_Draw_Pixel(param_1,&param_2->Vector,param_4.Color);
  return;
}
