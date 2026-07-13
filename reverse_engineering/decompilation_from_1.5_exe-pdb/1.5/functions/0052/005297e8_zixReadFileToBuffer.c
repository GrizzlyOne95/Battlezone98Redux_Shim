/*
 * Entry: 005297e8
 * Name: zixReadFileToBuffer
 * Namespace: Global
 * Signature: int zixReadFileToBuffer(char * param_1, int * param_2, void * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zixReadFileToBuffer(char *param_1,int *param_2,void *param_3,int param_4)

{
  void *pvVar1;
  void *unaff_EBX;
  int unaff_retaddr;
  
  pvVar1 = zixReadFileInternal(param_1,(int *)param_4,unaff_EBX,unaff_retaddr);
  return (uint)(pvVar1 != (void *)0x0);
}
