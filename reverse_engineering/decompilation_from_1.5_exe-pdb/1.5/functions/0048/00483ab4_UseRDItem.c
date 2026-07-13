/*
 * Entry: 00483ab4
 * Name: UseRDItem
 * Namespace: Global
 * Signature: void * UseRDItem(char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl UseRDItem(char *param_1,long param_2,long param_3)

{
  char *pcVar1;
  TEXTURE *pTVar2;
  
  pcVar1 = MakeRDName(param_1,(char *)0x0,param_2,param_3);
  if (pcVar1 != (char *)0x0) {
    param_1 = pcVar1;
  }
  pTVar2 = TexCache_UseTexture(param_1);
  return pTVar2;
}
