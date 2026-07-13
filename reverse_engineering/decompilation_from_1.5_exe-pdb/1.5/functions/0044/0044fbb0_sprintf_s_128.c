/*
 * Entry: 0044fbb0
 * Name: sprintf_s<128>
 * Namespace: Global
 * Signature: int sprintf_s<128>(char[128] * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sprintf_s<128>(char (*param_1) [128],char *param_2)

{
  int iVar1;
  
  iVar1 = vsprintf_s(*param_1,0x80,param_2,&stack0x0000000c);
  return iVar1;
}
