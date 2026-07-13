/*
 * Entry: 0050b93f
 * Name: AIBuild_ResourceIsClose
 * Namespace: Global
 * Signature: int AIBuild_ResourceIsClose(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_ResourceIsClose(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  iVar3 = 0;
  iVar2 = 0;
  do {
    iVar1 = AIBuild_ResourceListFind(param_1,iVar2,&local_8,&local_c);
    if (((iVar1 != 0) && ((param_2 - local_8) + 7U < 0xb)) && ((param_3 - local_c) + 7U < 0xb)) {
      iVar3 = 1;
    }
    iVar2 = iVar2 + 1;
  } while ((iVar1 != 0) && (iVar3 == 0));
  return iVar3;
}
