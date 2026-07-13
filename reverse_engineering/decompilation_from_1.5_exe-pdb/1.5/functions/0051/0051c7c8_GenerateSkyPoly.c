/*
 * Entry: 0051c7c8
 * Name: GenerateSkyPoly
 * Namespace: Global
 * Signature: void GenerateSkyPoly(tagActiveSkyAnim * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GenerateSkyPoly(tagActiveSkyAnim *param_1,CAMERA *param_2)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  POLYGON_SKIN PVar4;
  float fVar5;
  float *pfVar6;
  float *pfVar7;
  VECTOR_3D *pVVar8;
  int *unaff_EBX;
  POINT_3D local_304 [32];
  
  pVVar8 = (VECTOR_3D *)(unaff_EBX + 0xc);
  unaff_EBX[5] = (int)(((float)*(double *)(param_1[1].poly + 10) + 50.0) -
                      (float)unaff_EBX[8] * 0.01);
  Rot_Mat.posit_x = (double)(float)unaff_EBX[4];
  Rot_Mat.posit_y = (double)(float)unaff_EBX[5];
  Rot_Mat.posit_z = (double)(float)unaff_EBX[6];
  fVar5 = (float)unaff_EBX[8] * 0.01 * 0.5;
  fVar1 = (float)unaff_EBX[4];
  pVVar8->x = fVar1 - fVar5;
  unaff_EBX[0xd] = unaff_EBX[5];
  unaff_EBX[0xe] = (int)((float)unaff_EBX[6] - fVar5);
  unaff_EBX[0xf] = (int)((float)unaff_EBX[4] + fVar5);
  unaff_EBX[0x10] = unaff_EBX[5];
  unaff_EBX[0x11] = (int)((float)unaff_EBX[6] - fVar5);
  unaff_EBX[0x12] = (int)((float)unaff_EBX[4] + fVar5);
  unaff_EBX[0x13] = unaff_EBX[5];
  unaff_EBX[0x14] = (int)(fVar5 + (float)unaff_EBX[6]);
  unaff_EBX[0x15] = (int)(fVar1 - fVar5);
  unaff_EBX[0x16] = unaff_EBX[5];
  unaff_EBX[0x17] = (int)(fVar5 + (float)unaff_EBX[6]);
  Vector_Transform(pVVar8,pVVar8,4,(MAT_3D *)&param_1->poly[1].y);
  pfVar6 = &local_304[0].Texel.v;
  pfVar7 = uvTable[0][0] + 1;
  do {
    ((TEXEL *)(pfVar6 + -1))->u = (*(float (*) [2])(pfVar7 + -1))[0];
    fVar1 = *pfVar7;
    pfVar6[-4] = pVVar8->x;
    *pfVar6 = fVar1;
    pfVar3 = pfVar6 + -2;
    pfVar2 = &pVVar8->z;
    pfVar6[-3] = pVVar8->y;
    ((TEXEL_u_8 *)(pfVar6 + 1))->luma = 1.0;
    pfVar7 = pfVar7 + 2;
    pVVar8 = pVVar8 + 1;
    pfVar6 = pfVar6 + 6;
    *pfVar3 = *pfVar2;
  } while ((int)pfVar7 < 0x62f97c);
  PVar4 = *(POLYGON_SKIN *)(*unaff_EBX + unaff_EBX[3] * 4);
  if (useD3D == 0) {
    __Camera_Software_Draw_polygon__((CAMERA *)param_1,local_304,4,PVar4,0xc4);
  }
  else {
    __Camera_Hardware_Draw_polygon__((CAMERA *)param_1,local_304,4,PVar4,0xc4);
  }
  return;
}
