/*
 * Entry: 00483adc
 * Name: UnlockRDItem
 * Namespace: Global
 * Signature: void UnlockRDItem(char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnlockRDItem(char *param_1,long param_2,long param_3)

{
  char *pcVar1;
  
  pcVar1 = MakeRDName(param_1,(char *)0x0,param_2,param_3);
  if (pcVar1 != (char *)0x0) {
    param_1 = pcVar1;
  }
  TexCache_UnlockTexture(param_1);
  return;
}
