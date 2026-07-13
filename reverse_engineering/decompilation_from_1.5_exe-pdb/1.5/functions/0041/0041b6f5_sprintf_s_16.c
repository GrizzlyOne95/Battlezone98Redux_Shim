/*
 * Entry: 0041b6f5
 * Name: sprintf_s<16>
 * Namespace: Global
 * Signature: int sprintf_s<16>(char[16] * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sprintf_s<16>(char (*param_1) [16],char *param_2)

{
  int iVar1;
  
  iVar1 = vsprintf_s(*param_1,0x10,param_2,&stack0x0000000c);
  return iVar1;
}
