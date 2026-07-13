/*
 * Entry: 00477160
 * Name: Get_Tiled_Sky
 * Namespace: Global
 * Signature: long Get_Tiled_Sky(POINT_3D * param_1, CAMERA * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Get_Tiled_Sky(POINT_3D *param_1,CAMERA *param_2,float param_3)

{
  double dVar1;
  float fVar2;
  CAMERA *pCVar3;
  float fVar4;
  undefined1 extraout_AL;
  MAT_3D *pMVar5;
  long lVar6;
  int iVar7;
  float *pfVar8;
  TEXEL *pTVar9;
  MAT_3D *pMVar10;
  int iVar11;
  float10 fVar12;
  float10 extraout_ST0;
  POINT_3D local_244 [12];
  POINT_3D local_124 [6];
  MAT_3D local_94;
  MAT_3D local_54;
  float local_14;
  long local_10;
  float local_c;
  float local_8;
  
  pCVar3 = param_2;
  local_c = 1.0 / param_2->Const_x;
  local_8 = 1.0 / param_2->Const_y;
  if (useD3D == 0) {
    param_2 = (CAMERA *)TerrainIntensity;
    local_14 = (1.0 - TerrainIntensity) * 0.5;
  }
  else {
    local_14 = -127.5;
    param_2 = (CAMERA *)CONCAT22(param_2._2_2_,0xffff);
  }
  dVar1 = pCVar3->View_Pyramid[0].x;
  pMVar5 = &Identity_Matrix;
  pMVar10 = &local_54;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  fVar12 = (float10)floor(dVar1 * 0.001);
  local_54.posit_x = (double)(fVar12 * (float10)1000.0);
  fVar12 = (float10)floor();
  local_54.posit_z = (double)(fVar12 * (float10)1000.0);
  local_54.posit_y = (double)param_3;
  pMVar5 = Matrix_Multiply(&local_94,&local_54,&pCVar3->Matrix);
  pMVar10 = &local_54;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  pTVar9 = &local_124[0].Texel;
  iVar7 = 0;
  do {
    Vector_Transform((VECTOR_3D *)(pTVar9 + -1),(VECTOR_3D *)((int)&Sky_Vector[0].x + iVar7),1,
                     &local_54);
    iVar11 = iVar7 + 0xc;
    pTVar9->u = (float)Sky_Texture_U_Offset + *(float *)((int)&Sky_Texel[0].u + iVar7);
    pTVar9->v = (float)Sky_Texture_V_Offset + *(float *)((int)&Sky_Texel[0].v + iVar7);
    pTVar9->field2_0x8 = (TEXEL_u_8)param_2;
    pTVar9 = pTVar9 + 2;
    iVar7 = iVar11;
  } while (iVar11 < 0x30);
  iVar7 = __Clip_3D_UV_Polygon(pCVar3,local_244,local_124,4,2);
  if (iVar7 == 0) {
    lVar6 = 0;
  }
  else {
    local_10 = 0;
    if (0 < iVar7) {
      local_10 = iVar7;
      pfVar8 = &local_244[0].Vector.y;
      do {
        fVar2 = 1.0 / pfVar8[1];
        ((VECTOR_3D *)(pfVar8 + -1))->x =
             (((VECTOR_3D *)(pfVar8 + -1))->x - pCVar3->Orig_x) * fVar2 * local_c;
        *pfVar8 = (*pfVar8 - pCVar3->Orig_y) * fVar2 * local_8;
        iVar7 = iVar7 + -1;
        pfVar8[1] = fVar2;
        pfVar8 = pfVar8 + 6;
      } while (iVar7 != 0);
    }
    param_3 = (float)param_2;
    local_c = 1.4013e-45;
    do {
      fVar4 = local_c;
      fVar2 = param_3;
      fVar12 = (float10)(int)local_c;
      if (useD3D == 0) {
        param_3 = (float)((float10)local_14 * fVar12 + (float10)(float)param_2);
      }
      else {
        local_8 = (float)((uint)param_2 >> 8 & 0xff);
        _ftol2();
        param_3._0_2_ = CONCAT11(extraout_AL,param_3._0_1_);
        fVar12 = extraout_ST0;
      }
      local_8 = (float)((int)fVar4 + -1);
      lVar6 = ClipZ_UV_Poly((float)((float10)100.0 * (float10)(int)local_8 + (float10)300.0),
                            (float)(fVar12 * (float10)100.0 + (float10)300.0),param_1,local_244,
                            local_10,(tagLIGHTING)fVar2,(tagLIGHTING)param_3);
      if (lVar6 != 0) {
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__(pCVar3,param_1,lVar6,Sky_Texture,0x17);
        }
        else {
          __Camera_Hardware_Draw_polygon__(pCVar3,param_1,lVar6,Sky_Texture,0x17);
        }
      }
      local_c = (float)((int)fVar4 + 1);
    } while ((int)fVar4 < 2);
    lVar6 = ClipZ_UV_Poly(0.0,300.0,param_1,local_244,local_10,(tagLIGHTING)param_2,
                          (tagLIGHTING)param_2);
  }
  return lVar6;
}
