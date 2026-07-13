/*
 * Entry: 00529808
 * Name: zixReadFile
 * Namespace: Global
 * Signature: void * zixReadFile(char * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl zixReadFile(char *param_1,int *param_2)

{
  void *pvVar1;
  void *unaff_EBX;
  int unaff_retaddr;
  
  pvVar1 = zixReadFileInternal(param_1,(int *)0x0,unaff_EBX,unaff_retaddr);
  return pvVar1;
}
