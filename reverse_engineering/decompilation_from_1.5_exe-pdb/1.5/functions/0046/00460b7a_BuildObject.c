/*
 * Entry: 00460b7a
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(char * param_1, int param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(char *param_1,int param_2,char *param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int unaff_EDI;
  VECTOR_3D local_10;
  
  AiPath::Find(param_3);
  bVar1 = GetPosition((VECTOR_3D *)param_4,(AiPath *)param_3,unaff_EDI);
  if (!bVar1) {
    return 0;
  }
  iVar2 = BuildObject(param_1,param_2,&local_10);
  return iVar2;
}
