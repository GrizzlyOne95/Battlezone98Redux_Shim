/*
 * Entry: 0049bbac
 * Name: calc_poly_plane
 * Namespace: Global
 * Signature: PLANE * calc_poly_plane(PLANE * __return_storage_ptr__, FACE * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: __return_storage_ptr__ */

PLANE * __cdecl calc_poly_plane(PLANE *__return_storage_ptr__,FACE *param_1,VECTOR_3D *param_2)

{
  FACE *pFVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  FACE *pFVar6;
  PLANE *pPVar7;
  VECTOR_3D *pVVar8;
  VECTOR_3D *pVVar9;
  float *pfVar10;
  int iVar11;
  PLANE local_80;
  PLANE local_70;
  VECTOR_3D local_60;
  VECTOR_3D local_54;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  float *local_18;
  float local_14;
  VECTOR_3D *local_10;
  VECTOR_3D *local_c;
  float local_8;
  
  pFVar6 = param_1;
  fVar2 = 0.0;
  pFVar1 = (FACE *)param_1->vertex_count;
  (__return_storage_ptr__->surf_normal).x = 0.0;
  (__return_storage_ptr__->surf_normal).y = 0.0;
  (__return_storage_ptr__->surf_normal).z = 0.0;
  __return_storage_ptr__->dist = 0.0;
  if (2 < (int)pFVar1) {
    if (pFVar1 == (FACE *)0x3) {
      pVVar9 = param_2 + param_1[1].index;
      local_60.x = pVVar9->x;
      local_60.y = pVVar9->y;
      local_60.z = pVVar9->z;
      pVVar9 = param_2 + (int)param_1[1].plane.surf_normal.y;
      local_54.x = pVVar9->x;
      local_54.y = pVVar9->y;
      local_54.z = pVVar9->z;
      pVVar9 = param_2 + *(int *)param_1[1].texture_name;
      local_48.x = pVVar9->x;
      local_48.y = pVVar9->y;
      local_48.z = pVVar9->z;
      pPVar7 = Plane_Equation(&local_70,&local_60,&local_54,&local_48);
      (__return_storage_ptr__->surf_normal).x = (pPVar7->surf_normal).x;
      (__return_storage_ptr__->surf_normal).y = (pPVar7->surf_normal).y;
      (__return_storage_ptr__->surf_normal).z = (pPVar7->surf_normal).z;
      __return_storage_ptr__->dist = pPVar7->dist;
    }
    else if (pFVar1 != (FACE *)0x0) {
      pfVar10 = (float *)(param_1->texture_name + (int)&pFVar1->vertex_count * 0x10 + -0x20);
      pVVar9 = param_2 + param_1[1].index;
      param_1 = pFVar1;
      do {
        pfVar10 = pfVar10 + -4;
        pVVar8 = param_2 + (int)*pfVar10;
        param_1 = (FACE *)((int)&param_1[-1].Test_Point.z + 3);
        fVar3 = pVVar9->x - pVVar8->x;
        fVar4 = pVVar9->y - pVVar8->y;
        fVar5 = pVVar9->z - pVVar8->z;
        fVar3 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
        if (fVar2 < fVar3) {
          fVar2 = fVar3;
          local_10 = pVVar8;
          local_c = pVVar9;
        }
        pVVar9 = pVVar8;
      } while (param_1 != (FACE *)0x0);
      if (fVar2 != 0.0) {
        iVar11 = pFVar6->vertex_count;
        local_14 = -1.0;
        if (iVar11 != 0) {
          local_18 = (float *)(pFVar6[1].texture_name + iVar11 * 0x10 + -0x20);
          do {
            local_18 = local_18 + -4;
            pVVar9 = param_2 + (int)*local_18;
            iVar11 = iVar11 + -1;
            if ((pVVar9 != local_10) && (pVVar9 != local_c)) {
              local_30.x = local_c->x - local_10->x;
              local_30.y = local_c->y - local_10->y;
              local_30.z = local_c->z - local_10->z;
              local_3c.x = pVVar9->x - local_10->x;
              local_3c.y = pVVar9->y - local_10->y;
              local_3c.z = pVVar9->z - local_10->z;
              pVVar8 = Cross_Product((VECTOR_3D *)&local_70.surf_normal.y,&local_3c,&local_30);
              local_24 = pVVar8->x;
              local_20 = pVVar8->y;
              local_1c = pVVar8->z;
              local_8 = local_1c * local_1c + local_20 * local_20 + local_24 * local_24;
              if (local_14 < local_8) {
                pPVar7 = Plane_Equation(&local_80,local_10,local_c,pVVar9);
                local_14 = local_8;
                (__return_storage_ptr__->surf_normal).x = (pPVar7->surf_normal).x;
                (__return_storage_ptr__->surf_normal).y = (pPVar7->surf_normal).y;
                (__return_storage_ptr__->surf_normal).z = (pPVar7->surf_normal).z;
                __return_storage_ptr__->dist = pPVar7->dist;
              }
              if (16.0 < local_8) {
                return __return_storage_ptr__;
              }
            }
          } while (iVar11 != 0);
        }
      }
    }
  }
  return __return_storage_ptr__;
}
