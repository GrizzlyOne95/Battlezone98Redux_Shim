/*
 * Entry: 004750a6
 * Name: Cgeom_PointTest
 * Namespace: Global
 * Signature: int Cgeom_PointTest(POINT_VEL param_1, CLSN_GEOM * param_2, float param_3, float * param_4, VECTOR_3D * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Cgeom_PointTest(POINT_VEL param_1,CLSN_GEOM *param_2,float param_3,float *param_4,VECTOR_3D *param_5
               )

{
  long *plVar1;
  CLSN_GEOM *pCVar2;
  int iVar3;
  undefined4 *puVar4;
  VECTOR_3D *unaff_EDI;
  undefined4 *puVar5;
  POINT_VEL in_stack_ffffffac;
  _clsn_poly *p_Var6;
  VECTOR_3D *pVVar7;
  float *pfVar8;
  float *pfVar9;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float local_14;
  float fStack_10;
  float fStack_c;
  float local_8;
  
  pCVar2 = param_2;
  plVar1 = &param_2->poly_count;
  param_2 = (CLSN_GEOM *)param_2->polys;
  local_8 = 1e+30;
  if (param_2 < param_2 + *plVar1) {
    do {
      pfVar9 = &local_14;
      pfVar8 = &param_3;
      p_Var6 = (_clsn_poly *)pCVar2->verts;
      puVar5 = (undefined4 *)&stack0xffffffac;
      puVar4 = (undefined4 *)register0x00000010;
      pVVar7 = (VECTOR_3D *)param_3;
      for (iVar3 = 6; puVar4 = puVar4 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar5 = puVar5 + 1;
      }
      iVar3 = PointVelPoly(in_stack_ffffffac,p_Var6,pVVar7,(float)pfVar8,pfVar9,unaff_EDI);
      if ((iVar3 != 0) && (param_3 < local_8)) {
        local_8 = param_3;
        local_20 = local_14;
        fStack_1c = fStack_10;
        fStack_18 = fStack_c;
      }
      param_2 = param_2 + 1;
    } while (param_2 < (CLSN_GEOM *)(pCVar2->polys + pCVar2->poly_count));
    if (local_8 < 1e+30) {
      *param_4 = local_8;
      param_5->x = local_20;
      param_5->y = fStack_1c;
      param_5->z = fStack_18;
      return 1;
    }
  }
  return 0;
}
