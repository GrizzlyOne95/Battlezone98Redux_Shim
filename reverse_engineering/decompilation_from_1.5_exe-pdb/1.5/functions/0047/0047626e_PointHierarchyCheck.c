/*
 * Entry: 0047626e
 * Name: PointHierarchyCheck
 * Namespace: Global
 * Signature: int PointHierarchyCheck(POINT_VEL param_1, tagENTITY * param_2, float param_3, _OBJ76 * * param_4, float * param_5, VECTOR_3D * param_6, float param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointHierarchyCheck(POINT_VEL param_1,tagENTITY *param_2,float param_3,_OBJ76 **param_4,
                   float *param_5,VECTOR_3D *param_6,float param_7,int param_8)

{
  int *in_EAX;
  int iVar1;
  undefined4 *puVar2;
  POINT_VEL in_stack_ffffffbc;
  _OBJ76 *p_Var3;
  MAT_3D *pMVar4;
  
  p_Var3 = (_OBJ76 *)*in_EAX;
  if (p_Var3 == (_OBJ76 *)0x0) {
    iVar1 = 0;
  }
  else {
    pMVar4 = &Identity_Matrix;
    puVar2 = (undefined4 *)&stack0xffffffbc;
    for (iVar1 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar1 != 0;
        iVar1 = iVar1 + -1) {
      *puVar2 = *(undefined4 *)register0x00000010;
      puVar2 = puVar2 + 1;
    }
    iVar1 = PointRecurse(in_stack_ffffffbc,p_Var3,pMVar4,(float)param_2,(_OBJ76 **)param_3,
                         (float *)param_4,(VECTOR_3D *)param_5,(float)param_6,(int)param_7);
  }
  return iVar1;
}
