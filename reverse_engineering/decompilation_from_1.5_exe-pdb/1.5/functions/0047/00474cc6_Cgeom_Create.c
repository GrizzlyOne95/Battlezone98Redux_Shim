/*
 * Entry: 00474cc6
 * Name: Cgeom_Create
 * Namespace: Global
 * Signature: CLSN_GEOM * Cgeom_Create(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

CLSN_GEOM * __cdecl Cgeom_Create(_OBJ76 *param_1,MAT_3D *param_2)

{
  CLSN_GEOM *pCVar1;
  float *pfVar2;
  int iVar3;
  long *plVar4;
  undefined4 *puVar5;
  FACE *pFVar6;
  CLSN_GEOM *pCVar7;
  VECTOR_3D *pVVar8;
  uint uVar9;
  int iVar10;
  _GEOMETRY *p_Var11;
  undefined4 *puVar12;
  char *pcVar13;
  int iVar14;
  float fVar15;
  float fStack_60;
  VECTOR_3D VStack_5c;
  VECTOR_3D VStack_50;
  undefined1 local_38 [12];
  undefined4 *local_2c;
  undefined1 *local_28;
  FACE *local_24;
  _GEOMETRY *local_20;
  FACE *local_1c;
  int local_18;
  int local_14;
  FACE *local_10;
  int local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var11 = param_1->geom;
  iVar3 = p_Var11->vertex_count;
  local_20 = p_Var11;
  VStack_50.z = 6.547919e-39;
  local_1c = (FACE *)(&stack0xffffffbc + iVar3 * -0xc);
  (&VStack_50)[-iVar3].z = 6.547934e-39;
  local_28 = &stack0xffffffbc + iVar3 * -0xe;
  local_18 = 0;
  local_14 = 0;
  if (0 < iVar3) {
    local_10 = (FACE *)0x0;
    do {
      local_c = 0;
      if (0 < local_18) {
        local_2c = (undefined4 *)((int)&p_Var11->vertex_table->x + (int)local_10);
        local_24 = local_1c;
        do {
          puVar5 = local_2c;
          puVar12 = local_2c + 1;
          *(undefined4 *)((int)&VStack_50 + iVar3 * -0xe) = *local_2c;
          *(undefined4 *)((int)&VStack_50 + iVar3 * -0xe + 4) = *puVar12;
          *(undefined4 *)((int)&VStack_50 + iVar3 * -0xe + 8) = puVar5[2];
          pFVar6 = local_24;
          pfVar2 = (float *)&local_24->vertex_count;
          *(long *)((int)&VStack_5c + iVar3 * -0xe) = local_24->index;
          *(float *)((int)&VStack_5c + iVar3 * -0xe + 4) = *pfVar2;
          *(COLOR *)((int)&VStack_5c + iVar3 * -0xe + 8) = pFVar6->color;
          *(undefined4 *)((int)&fStack_60 + iVar3 * -0xe) = 0x474d46;
          fVar15 = Dist3D_Squared(*(VECTOR_3D *)((int)&VStack_5c + iVar3 * -0xe),
                                  *(VECTOR_3D *)((int)&VStack_50 + iVar3 * -0xe));
          p_Var11 = local_20;
          if (fVar15 < 0.0001) break;
          local_c = local_c + 1;
          local_24 = (FACE *)&local_24->plane;
        } while (local_c < local_18);
      }
      *(short *)(local_28 + local_14 * 2) = (short)local_c;
      if (local_c == local_18) {
        puVar12 = (undefined4 *)((int)&p_Var11->vertex_table->x + (int)local_10);
        pcVar13 = local_1c->texture_name + local_c * 0xc + -0x20;
        local_18 = local_18 + 1;
        *(undefined4 *)pcVar13 = *puVar12;
        *(undefined4 *)(pcVar13 + 4) = puVar12[1];
        *(undefined4 *)(pcVar13 + 8) = puVar12[2];
        p_Var11 = local_20;
      }
      local_14 = local_14 + 1;
      local_10 = (FACE *)((int)local_10 + 0xc);
    } while (local_14 < iVar3);
  }
  uVar9 = 0;
  iVar14 = 0;
  for (pFVar6 = p_Var11->faces; pFVar6 != (FACE *)0x0; pFVar6 = pFVar6->front_facet) {
    if (2 < pFVar6->vertex_count) {
      uVar9 = uVar9 + pFVar6->vertex_count;
      iVar14 = iVar14 + 1;
    }
  }
  iVar10 = uVar9 + (uVar9 & 1);
  *(int *)((int)&VStack_50 + iVar3 * -0xe + 8) = ((local_18 + 2 + iVar14 * 2) * 6 + iVar10) * 2;
  local_c = iVar10;
  *(undefined4 *)((int)&VStack_50 + iVar3 * -0xe + 4) = 0x474dd9;
  pCVar7 = malloc(*(size_t *)((int)&VStack_50 + iVar3 * -0xe + 8));
  iVar10 = local_18;
  if (pCVar7 != (CLSN_GEOM *)0x0) {
    pCVar7->vtx_count = local_18;
    pCVar1 = pCVar7 + 1;
    pCVar7->idx_count = local_c;
    *(int *)((int)&VStack_50 + iVar3 * -0xe + 8) = local_18 * 0xc;
    *(FACE **)((int)&VStack_50 + iVar3 * -0xe + 4) = local_1c;
    pCVar7->poly_count = iVar14;
    pCVar7->indices = (ushort *)(&pCVar1->vtx_count + iVar10 * 3);
    iVar14 = local_c * 2;
    *(CLSN_GEOM **)((int)&VStack_50 + iVar3 * -0xe) = pCVar1;
    pCVar7->verts = (VECTOR_3D *)pCVar1;
    pCVar7->polys = (_clsn_poly *)((int)(&pCVar1->vtx_count + iVar10 * 3) + iVar14);
    *(undefined4 *)((int)&VStack_5c + iVar3 * -0xe + 8) = 0x474e14;
    memcpy();
    pFVar6 = p_Var11->faces;
    local_c = 0;
    local_20 = (_GEOMETRY *)pCVar7->polys;
    local_10 = pFVar6;
    while (pFVar6 != (FACE *)0x0) {
      local_10 = pFVar6;
      if (2 < pFVar6->vertex_count) {
        *(float *)((int)&VStack_50 + iVar3 * -0xe) = (pFVar6->plane).surf_normal.x;
        *(float *)((int)&VStack_50 + iVar3 * -0xe + 4) = (pFVar6->plane).surf_normal.y;
        *(undefined1 **)((int)&VStack_5c + iVar3 * -0xe + 8) = local_38;
        *(float *)((int)&VStack_50 + iVar3 * -0xe + 8) = (pFVar6->plane).surf_normal.z;
        *(undefined4 *)((int)&VStack_5c + iVar3 * -0xe + 4) = 0x474e4e;
        pVVar8 = NegVector(*(VECTOR_3D **)((int)&VStack_5c + iVar3 * -0xe + 8),
                           *(VECTOR_3D *)((int)&VStack_50 + iVar3 * -0xe));
        local_14 = 0;
        (((PLANE *)&local_20->cache_info)->surf_normal).x = pVVar8->x;
        (((PLANE *)&local_20->cache_info)->surf_normal).y = pVVar8->y;
        (((PLANE *)&local_20->cache_info)->surf_normal).z = pVVar8->z;
        ((PLANE *)&local_20->cache_info)->dist = -(local_10->plane).dist;
        iVar14 = local_10->vertex_count;
        local_20->normal_table = (VECTOR_3D *)iVar14;
        local_20->faces = (FACE *)(pCVar7->indices + local_c);
        if (0 < iVar14) {
          local_1c = local_10 + 1;
          do {
            iVar10 = local_14;
            plVar4 = &local_1c->index;
            local_14 = local_14 + 1;
            local_1c = (FACE *)&(local_1c->plane).surf_normal.y;
            *(ushort *)((int)local_20->faces + iVar10 * 2) = *(ushort *)(local_28 + *plVar4 * 2);
          } while (local_14 < iVar14);
        }
        local_c = local_c + iVar14;
        local_20 = (_GEOMETRY *)(local_20 + 1);
      }
      pFVar6 = local_10->front_facet;
      local_10 = pFVar6;
    }
  }
  return pCVar7;
}
