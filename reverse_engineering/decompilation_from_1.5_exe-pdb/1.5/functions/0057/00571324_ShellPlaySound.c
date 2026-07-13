/*
 * Entry: 00571324
 * Name: ShellPlaySound
 * Namespace: Global
 * Signature: void * ShellPlaySound(char * param_1, long param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl ShellPlaySound(char *param_1,long param_2,long param_3,long param_4)

{
  uchar *puVar1;
  
  puVar1 = UseItem(param_1);
  if (puVar1 == (uchar *)0x0) {
    puVar1 = (uchar *)0x0;
  }
  else {
    ShellStartGASEvent(puVar1,param_2,param_3,param_4);
    NextGAS(0);
    UnlockItem(param_1);
  }
  return puVar1;
}
