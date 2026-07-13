/*
 * Entry: 004758b6
 * Name: CollectFloorFaces
 * Namespace: Global
 * Signature: void CollectFloorFaces(CLSN_GEOM * param_1, _OBJ76 * param_2, tagENTITY * param_3, MAT_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
CollectFloorFaces(CLSN_GEOM *param_1,_OBJ76 *param_2,tagENTITY *param_3,MAT_3D *param_4)

{
  float fVar1;
  ushort *puVar2;
  uint uVar3;
  VECTOR_3D *pVVar4;
  long *plVar5;
  float *pfVar6;
  _clsn_poly *p_Var7;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float fStack_18;
  _clsn_poly *local_14;
  float *local_10;
  _clsn_poly *local_c;
  uint local_8;
  
  local_10 = (float *)param_1->vtx_count;
  local_8 = 0;
  local_c = (_clsn_poly *)0x0;
  p_Var7 = param_1->polys;
  local_14 = p_Var7 + param_1->poly_count;
  if (p_Var7 < local_14) {
    do {
      pVVar4 = Vector_Rotate(&local_2c,(VECTOR_3D *)p_Var7,(MAT_3D *)param_3);
      local_20 = pVVar4->x;
      local_1c = pVVar4->y;
      fStack_18 = pVVar4->z;
      if (0.4 < local_1c) {
        local_8 = local_8 + p_Var7->vtx_count;
        local_c = (_clsn_poly *)((int)local_c + 1);
      }
      p_Var7 = p_Var7 + 1;
    } while (p_Var7 < local_14);
    if (local_c != (_clsn_poly *)0x0) {
      local_8 = local_8 + (local_8 & 1);
      plVar5 = malloc((((int)local_10 + (int)local_c * 2) * 3 + local_8) * 4 + 0x1c);
      pVVar4 = (VECTOR_3D *)(plVar5 + 7);
      plVar5[3] = (long)(pVVar4 + (int)local_10);
      *plVar5 = (long)local_10;
      plVar5[1] = (long)pVVar4;
      plVar5[2] = local_8;
      plVar5[4] = (long)local_c;
      plVar5[5] = (int)&pVVar4[(int)local_10].x + local_8 * 2;
      Vector_Transform(pVVar4,param_1->verts,(long)local_10,(MAT_3D *)param_3);
      local_10 = (float *)plVar5[5];
      local_8 = 0;
      local_c = param_1->polys;
      if (local_c < local_c + param_1->poly_count) {
        do {
          pVVar4 = Vector_Rotate(&local_2c,(VECTOR_3D *)local_c,(MAT_3D *)param_3);
          uVar3 = local_8;
          pfVar6 = local_10;
          local_20 = pVVar4->x;
          local_1c = pVVar4->y;
          fStack_18 = pVVar4->z;
          if (0.4 < local_1c) {
            local_10[4] = (float)local_c->vtx_count;
            fVar1 = (float)(plVar5[3] + local_8 * 2);
            local_10[5] = fVar1;
            memcpy(fVar1,local_c->vtxlist,(int)local_10[4] * 2);
            local_8 = uVar3 + (int)pfVar6[4];
            pVVar4 = Vector_Rotate(&local_38,(VECTOR_3D *)local_c,(MAT_3D *)param_3);
            puVar2 = (ushort *)local_10[5];
            *pfVar6 = pVVar4->x;
            pfVar6[1] = pVVar4->y;
            pfVar6[2] = pVVar4->z;
            pfVar6 = (float *)((uint)*puVar2 * 0xc + plVar5[1]);
            local_10[3] = -(*local_10 * *pfVar6 + pfVar6[1] * local_10[1] + pfVar6[2] * local_10[2])
            ;
            local_10 = local_10 + 6;
          }
          local_c = local_c + 1;
        } while (local_c < param_1->polys + param_1->poly_count);
      }
      plVar5[6] = (long)(param_2->transform).right_z;
      (param_2->transform).right_z = (float)plVar5;
    }
  }
  return;
}
