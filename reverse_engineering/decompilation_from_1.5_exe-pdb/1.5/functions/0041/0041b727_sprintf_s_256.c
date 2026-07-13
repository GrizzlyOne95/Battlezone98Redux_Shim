/*
 * Entry: 0041b727
 * Name: sprintf_s<256>
 * Namespace: Global
 * Signature: int sprintf_s<256>(char[256] * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sprintf_s<256>(char (*param_1) [256],char *param_2)

{
  int iVar1;
  
  iVar1 = vsprintf_s(*param_1,0x100,param_2,&stack0x0000000c);
  return iVar1;
}
