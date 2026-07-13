/*
 * Entry: 00476c2b
 * Name: Get_Top_Sky
 * Namespace: Global
 * Signature: long Get_Top_Sky(POINT_3D * param_1, CAMERA * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Get_Top_Sky(POINT_3D *param_1,CAMERA *param_2,float param_3)

{
  PLANE *pPVar1;
  long lVar2;
  float *unaff_EBX;
  long unaff_ESI;
  float unaff_EDI;
  PLANE local_b8;
  POINT_3D local_a8;
  float local_90;
  float local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
  float local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  PLANE local_18;
  float local_8;
  
  if (useD3D == 0) {
    local_8 = TerrainIntensity;
  }
  else {
    local_8 = (float)CONCAT22(local_8._2_2_,0xff00);
    local_8 = (float)CONCAT31(local_8._1_3_,0xff);
  }
  local_a8.Vector.x = unaff_EBX[5];
  local_a8.Vector.y = unaff_EBX[6];
  local_a8.Vector.z = 0.00076687115;
  local_a8.Texel.u = 0.0;
  local_a8.Texel.v = 0.0;
  local_a8.Texel.field2_0x8.luma = local_8;
  local_90 = unaff_EBX[7];
  local_8c = unaff_EBX[6];
  local_88 = 0x3a4907da;
  local_84 = 0;
  local_80 = 0;
  local_7c = local_8;
  local_78 = unaff_EBX[7];
  local_74 = unaff_EBX[8];
  local_70 = 0x3a4907da;
  local_6c = 0;
  local_68 = 0;
  local_64 = local_8;
  local_60 = unaff_EBX[5];
  local_5c = unaff_EBX[8];
  local_58 = 0x3a4907da;
  local_54 = 0;
  local_50 = 0;
  local_18.surf_normal.x = 0.0;
  local_4c = local_8;
  local_18.surf_normal.y = 1.0;
  local_18.surf_normal.z = 0.0;
  local_18.dist = -(float)param_2;
  pPVar1 = Plane_Transform(&local_b8,&local_18,(MAT_3D *)(unaff_EBX + 0x10));
  local_18.surf_normal.x = (pPVar1->surf_normal).x;
  local_18.surf_normal.y = (pPVar1->surf_normal).y;
  local_18.surf_normal.z = (pPVar1->surf_normal).z;
  local_18.dist = pPVar1->dist;
  lVar2 = Line_Clip_Polygon(&local_a8,(POINT_3D *)(local_18.surf_normal.x * (1.0 / unaff_EBX[2])),
                            local_18.surf_normal.y * (1.0 / unaff_EBX[3]),
                            local_18.dist / unaff_EBX[0x4e] +
                            ((local_18.surf_normal.z -
                             *unaff_EBX * (1.0 / unaff_EBX[2]) * local_18.surf_normal.x) -
                            unaff_EBX[1] * (1.0 / unaff_EBX[3]) * local_18.surf_normal.y),local_8,
                            unaff_EDI,unaff_ESI);
  return lVar2;
}
