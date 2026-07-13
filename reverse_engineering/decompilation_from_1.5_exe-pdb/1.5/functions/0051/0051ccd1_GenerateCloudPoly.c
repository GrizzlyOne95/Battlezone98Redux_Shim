/*
 * Entry: 0051ccd1
 * Name: GenerateCloudPoly
 * Namespace: Global
 * Signature: void GenerateCloudPoly(CAMERA * param_1, TEXTURE * param_2, VECTOR_3D * param_3, float param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
GenerateCloudPoly(CAMERA *param_1,TEXTURE *param_2,VECTOR_3D *param_3,float param_4,int param_5)

{
  VECTOR_3D *pVVar1;
  float *in_EAX;
  int in_ECX;
  VECTOR_3D *pVVar2;
  float *pfVar3;
  float *pfVar4;
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
  
  pVVar1 = param_3;
  local_184.x = *in_EAX - (float)param_3;
  pfVar4 = uvTable[in_ECX][0] + 1;
  pVVar2 = &local_184;
  local_184.y = in_EAX[1];
  pfVar3 = &local_484[0].Texel.v;
  param_3 = (VECTOR_3D *)0x4;
  local_184.z = in_EAX[2] - (float)pVVar1;
  local_178 = *in_EAX + (float)pVVar1;
  local_174 = in_EAX[1];
  local_168 = in_EAX[1];
  local_164 = in_EAX[2] + (float)pVVar1;
  local_15c = in_EAX[1];
  local_170 = local_184.z;
  local_16c = local_178;
  local_160 = local_184.x;
  local_158 = local_164;
  do {
    ((TEXEL *)(pfVar3 + -1))->u = (*(float (*) [2])(pfVar4 + -1))[0];
    *pfVar3 = *pfVar4;
    ((TEXEL_u_8 *)(pfVar3 + 1))->luma = 1.0;
    Vector_Transform((VECTOR_3D *)(pfVar3 + -4),pVVar2,1,&param_1->Matrix);
    pfVar4 = pfVar4 + 2;
    pVVar2 = pVVar2 + 1;
    pfVar3 = pfVar3 + 6;
    param_3 = (VECTOR_3D *)((int)&param_3[-1].z + 3);
  } while (param_3 != (VECTOR_3D *)0x0);
  if (useD3D == 0) {
    __Camera_Software_Draw_polygon__(param_1,local_484,4,(POLYGON_SKIN)param_2,0xd4);
  }
  else {
    __Camera_Hardware_Draw_polygon__(param_1,local_484,4,(POLYGON_SKIN)param_2,0xd4);
  }
  return;
}
