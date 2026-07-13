/*
 * Entry: 00476d60
 * Name: Get_Shaded_Sky
 * Namespace: Global
 * Signature: long Get_Shaded_Sky(POINT_3D * param_1, CAMERA * param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Get_Shaded_Sky(POINT_3D *param_1,CAMERA *param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  PLANE *pPVar5;
  float *unaff_EBX;
  double dVar6;
  PLANE local_40;
  PLANE local_30;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  if (useD3D == 0) {
    local_c = 1.0;
    local_1c = TerrainIntensity;
  }
  else {
    local_c = (float)CONCAT22(local_c._2_2_,0xff);
    local_1c = (float)CONCAT22(local_1c._2_2_,0xffff);
  }
  local_18 = (param_1[1].Vector.y - (param_1->Texel).field2_0x8.luma) * 0.7;
  local_10 = ((param_1->Texel).field2_0x8.luma + param_1[1].Vector.y) * 0.5;
  local_14 = (param_1[1].Vector.z + param_1[1].Vector.x) * 0.5;
  local_30.surf_normal.x = 0.0;
  local_30.surf_normal.z = 0.0;
  local_30.surf_normal.y = 1.0;
  local_30.dist = -(float)param_2;
  pPVar5 = Plane_Transform(&local_40,&local_30,(MAT_3D *)&param_1[2].Texel.v);
  local_30.surf_normal.x = (pPVar5->surf_normal).x;
  local_30.surf_normal.y = (pPVar5->surf_normal).y;
  local_30.surf_normal.z = (pPVar5->surf_normal).z;
  local_30.dist = pPVar5->dist;
  fVar1 = 1.0 / (param_1->Vector).z;
  fVar2 = local_30.surf_normal.x * fVar1;
  fVar3 = 1.0 / (param_1->Texel).u;
  local_8 = local_30.surf_normal.y * fVar3;
  local_20 = local_30.dist / param_1[0xd].Vector.x +
             ((local_30.surf_normal.z - (param_1->Vector).x * fVar1 * local_30.surf_normal.x) -
             fVar3 * local_30.surf_normal.y * (param_1->Vector).y);
  fVar1 = fVar2 * fVar2 + local_8 * local_8;
  if (1e-09 <= fVar1) {
    dVar6 = rsqrt((double)fVar1);
    fVar1 = (float)dVar6;
    fVar2 = fVar2 * fVar1;
    fVar4 = fVar1 * local_8;
    fVar1 = fVar2 * local_10 + local_14 * fVar4 + local_20 * fVar1;
    fVar3 = local_10 - fVar1 * fVar2;
    fVar1 = local_14 - fVar1 * fVar4;
    *unaff_EBX = fVar3 - fVar4 * local_18;
    unaff_EBX[1] = fVar2 * local_18 + fVar1;
    unaff_EBX[2] = 0.00076687115;
    unaff_EBX[3] = 0.0;
    unaff_EBX[4] = 0.0;
    unaff_EBX[5] = local_c;
    unaff_EBX[6] = fVar4 * local_18 + fVar3;
    unaff_EBX[7] = fVar1 - fVar2 * local_18;
    unaff_EBX[8] = 0.00076687115;
    unaff_EBX[9] = 0.0;
    unaff_EBX[10] = 0.0;
    unaff_EBX[0xb] = local_c;
    local_30.surf_normal.x = 0.0;
    local_30.surf_normal.y = 1.0;
    local_30.surf_normal.z = 0.0;
    local_30.dist = -param_3;
    pPVar5 = Plane_Transform(&local_40,&local_30,(MAT_3D *)&param_1[2].Texel.v);
    fVar1 = 1.0 / (param_1->Vector).z;
    local_30.surf_normal.x = (pPVar5->surf_normal).x;
    local_30.surf_normal.y = (pPVar5->surf_normal).y;
    local_30.surf_normal.z = (pPVar5->surf_normal).z;
    local_30.dist = pPVar5->dist;
    fVar2 = local_30.surf_normal.x * fVar1;
    fVar3 = 1.0 / (param_1->Texel).u;
    local_8 = local_30.surf_normal.y * fVar3;
    local_20 = local_30.dist / param_1[0xd].Vector.x +
               ((local_30.surf_normal.z - fVar1 * (param_1->Vector).x * local_30.surf_normal.x) -
               fVar3 * local_30.surf_normal.y * (param_1->Vector).y);
    fVar1 = fVar2 * fVar2 + local_8 * local_8;
    if (1e-09 <= fVar1) {
      dVar6 = rsqrt((double)fVar1);
      fVar1 = (float)dVar6;
      fVar2 = fVar2 * fVar1;
      local_8 = fVar1 * local_8;
      fVar1 = fVar2 * local_10 + local_14 * local_8 + local_20 * fVar1;
      local_10 = local_10 - fVar1 * fVar2;
      local_14 = local_14 - fVar1 * local_8;
      unaff_EBX[0xc] = local_8 * local_18 + local_10;
      unaff_EBX[0xd] = local_14 - fVar2 * local_18;
      unaff_EBX[0xe] = 0.00076687115;
      unaff_EBX[0xf] = 0.0;
      unaff_EBX[0x10] = 0.0;
      unaff_EBX[0x11] = local_1c;
      unaff_EBX[0x12] = local_10 - local_8 * local_18 * 2.0;
      unaff_EBX[0x13] = fVar2 * local_18 * 2.0 + local_14;
      unaff_EBX[0x14] = 0.00076687115;
      unaff_EBX[0x15] = 0.0;
      unaff_EBX[0x16] = 0.0;
      unaff_EBX[0x17] = local_1c;
      return 4;
    }
  }
  return 0;
}
