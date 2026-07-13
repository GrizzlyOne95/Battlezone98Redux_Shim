/*
 * Entry: 00460bb3
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(char * param_1, int param_2, AiPath * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(char *param_1,int param_2,AiPath *param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  AiPath *unaff_EDI;
  float in_stack_fffffff0;
  
  bVar1 = GetPosition((VECTOR_3D *)param_4,unaff_EDI,(int)in_stack_fffffff0);
  if (!bVar1) {
    return 0;
  }
  iVar2 = BuildObject(param_1,param_2,(VECTOR_3D *)&stack0xfffffff0);
  return iVar2;
}
