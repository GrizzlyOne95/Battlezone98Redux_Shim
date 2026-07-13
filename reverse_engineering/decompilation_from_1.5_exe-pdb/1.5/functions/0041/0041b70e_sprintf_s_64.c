/*
 * Entry: 0041b70e
 * Name: sprintf_s<64>
 * Namespace: Global
 * Signature: int sprintf_s<64>(char[64] * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sprintf_s<64>(char (*param_1) [64],char *param_2)

{
  int iVar1;
  
  iVar1 = vsprintf_s(*param_1,0x40,param_2,&stack0x0000000c);
  return iVar1;
}
