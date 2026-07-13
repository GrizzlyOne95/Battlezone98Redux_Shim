/*
 * Entry: 0051c4ba
 * Name: GenerateAnimPoly
 * Namespace: Global
 * Signature: void GenerateAnimPoly(tagActiveAnim * param_1, CAMERA * param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GenerateAnimPoly(tagActiveAnim *param_1,CAMERA *param_2,float param_3,float param_4)

{
  _ZSORTING *p_Var1;
  VECTOR_3D *pVVar2;
  MAT_3D *pMVar3;
  int iVar4;
  int *unaff_EBX;
  float *pfVar5;
  MAT_3D *pMVar6;
  _ZSORTING *p_Var7;
  float fVar8;
  MAT_3D local_b0;
  MAT_3D local_70;
  VECTOR_3D local_30;
  float local_24;
  float fStack_20;
  float local_1c;
  _ZSORTING *local_18;
  float *local_14;
  VECTOR_3D *local_10;
  int local_c;
  float *local_8;
  
  Rot_Mat.posit_x = (double)(float)unaff_EBX[4];
  Rot_Mat.posit_y = (double)(float)unaff_EBX[5];
  Rot_Mat.posit_z = (double)(float)unaff_EBX[6];
  pVVar2 = Camera_World_to_Camera
                     (&local_30,(CAMERA *)param_1,(double)(float)unaff_EBX[4],
                      (double)(float)unaff_EBX[5],(double)(float)unaff_EBX[6]);
  local_24 = pVVar2->x;
  fStack_20 = pVVar2->y;
  local_1c = pVVar2->z;
  if (local_1c <= Terrain.Grid_Size * TerrainVisibilityRange) {
    fVar8 = (float)param_2 * 0.5;
    unaff_EBX[10] = (int)-fVar8;
    unaff_EBX[0xb] = 0;
    unaff_EBX[0xc] = 0;
    unaff_EBX[0xe] = 0;
    unaff_EBX[0xf] = 0;
    unaff_EBX[0xd] = (int)fVar8;
    unaff_EBX[0x10] = (int)fVar8;
    unaff_EBX[0x11] = (int)param_3;
    unaff_EBX[0x12] = 0;
    unaff_EBX[0x13] = (int)-fVar8;
    unaff_EBX[0x14] = (int)param_3;
    unaff_EBX[0x15] = 0;
    pMVar3 = Matrix_Multiply(&local_b0,&Rot_Mat,(MAT_3D *)(param_1->poly + 2));
    pMVar6 = &local_70;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    pVVar2 = (VECTOR_3D *)(unaff_EBX + 10);
    Vector_Transform(pVVar2,pVVar2,4,&local_70);
    p_Var1 = SortingTableCurrent;
    local_c = 0;
    local_18 = SortingTableCurrent;
    SortingTableCurrent->Type = 8;
    p_Var1->vcnt = 4;
    local_8 = uvTable[0][0] + 1;
    pfVar5 = &p_Var1[1].Z_Value;
    local_10 = pVVar2;
    do {
      pfVar5[-1] = (*(float (*) [2])(local_8 + -1))[0];
      *pfVar5 = *local_8;
      local_14 = pfVar5;
      p_Var7 = (_ZSORTING *)
               DepthAttenuation(TerrainIntensity,*(float *)((int)&Vertex_Pool->z + local_c));
      p_Var1 = local_18;
      local_8 = local_8 + 2;
      pfVar5[1] = (float)p_Var7;
      local_c = local_c + 0xc;
      local_14 = local_14 + 6;
      pVVar2 = local_10 + 1;
      ((_ZSORTING *)(pfVar5 + -4))->vcnt = (long)local_10->x;
      *(float *)(pfVar5 + -3) = local_10->y;
      pfVar5[-2] = local_10->z;
      pfVar5 = local_14;
      local_10 = pVVar2;
    } while ((int)local_8 < 0x62f97c);
    fVar8 = GetMax((POINT_3D *)(local_18 + 1),local_18->vcnt);
    p_Var1->Z_Value = fVar8;
    (p_Var1->Skin_Color).Color = 0;
    p_Var1->Bitmap_Operation = 0x44;
    p_Var1->Skin_Color = *(POLYGON_SKIN *)(*unaff_EBX + unaff_EBX[2] * 4);
    ZSORTAdd(fVar8);
  }
  return;
}
