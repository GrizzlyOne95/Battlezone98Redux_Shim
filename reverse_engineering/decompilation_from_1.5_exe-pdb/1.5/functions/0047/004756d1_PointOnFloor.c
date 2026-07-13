/*
 * Entry: 004756d1
 * Name: PointOnFloor
 * Namespace: Global
 * Signature: int PointOnFloor(VECTOR_2D param_1, tagENTITY * param_2, float * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PointOnFloor(VECTOR_2D param_1,tagENTITY *param_2,float *param_3,VECTOR_3D *param_4)

{
  int in_EAX;
  int iVar1;
  _clsn_poly *p_Var2;
  _clsn_poly *p_Var3;
  int iVar4;
  _OBJ76 *p_Var5;
  
  iVar4 = *(int *)(in_EAX + 0x28);
  do {
    if (iVar4 == 0) {
      return 0;
    }
    p_Var3 = *(_clsn_poly **)(iVar4 + 0x14);
    p_Var2 = p_Var3 + *(int *)(iVar4 + 0x10);
    for (; p_Var3 < p_Var2; p_Var3 = p_Var3 + 1) {
      iVar1 = inside_polyxz(p_Var3,*(VECTOR_3D **)(iVar4 + 4),param_1.x,param_1.z);
      if (iVar1 != 0) {
        p_Var5 = (_OBJ76 *)Cgeom_PolyHeight(p_Var3,param_1.x,param_1.z);
        param_2->obj76 = p_Var5;
        *param_3 = (p_Var3->plane).surf_normal.x;
        param_3[1] = (p_Var3->plane).surf_normal.y;
        param_3[2] = (p_Var3->plane).surf_normal.z;
        return 1;
      }
      p_Var2 = (_clsn_poly *)(*(int *)(iVar4 + 0x10) * 0x18 + *(int *)(iVar4 + 0x14));
    }
    iVar4 = *(int *)(iVar4 + 0x18);
  } while( true );
}
