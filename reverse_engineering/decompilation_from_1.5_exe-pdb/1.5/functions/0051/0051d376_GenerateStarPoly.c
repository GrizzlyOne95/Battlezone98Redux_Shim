/*
 * Entry: 0051d376
 * Name: GenerateStarPoly
 * Namespace: Global
 * Signature: void GenerateStarPoly(CAMERA * param_1, TEXTURE * param_2, MAT_3D * param_3, float param_4, float param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
GenerateStarPoly(CAMERA *param_1,TEXTURE *param_2,MAT_3D *param_3,float param_4,float param_5,
                int param_6)

{
  VECTOR_3D *pVVar1;
  float *pfVar2;
  float *pfVar3;
  POINT_3D local_484 [32];
  VECTOR_3D local_184;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  
  local_184.x = -param_4;
  pVVar1 = &local_184;
  pfVar2 = &local_484[0].Texel.v;
  local_184.z = param_5;
  pfVar3 = uvTable[0][0] + 1;
  local_170 = param_5;
  local_164 = param_5;
  local_158 = param_5;
  local_178 = param_4;
  local_16c = param_4;
  local_168 = param_4;
  local_15c = param_4;
  local_184.y = local_184.x;
  local_174 = local_184.x;
  local_160 = local_184.x;
  do {
    ((TEXEL *)(pfVar2 + -1))->u = (*(float (*) [2])(pfVar3 + -1))[0];
    *pfVar2 = *pfVar3;
    ((TEXEL_u_8 *)(pfVar2 + 1))->luma = 1.0;
    Vector_Transform((VECTOR_3D *)(pfVar2 + -4),pVVar1,1,param_3);
    pfVar3 = pfVar3 + 2;
    pVVar1 = pVVar1 + 1;
    pfVar2 = pfVar2 + 6;
  } while ((int)pfVar3 < 0x62f97c);
  if (useD3D == 0) {
    __Camera_Software_Draw_polygon__(param_1,local_484,4,(POLYGON_SKIN)param_2,param_6);
  }
  else {
    __Camera_Hardware_Draw_polygon__(param_1,local_484,4,(POLYGON_SKIN)param_2,param_6);
  }
  return;
}
