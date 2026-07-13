/*
 * Entry: 00525393
 * Name: initLZO
 * Namespace: Global
 * Signature: int initLZO(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl initLZO(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = (char *)0x2080;
  iVar1 = __lzo_init_v2(0x2080,2,4,4,4,4,4,4,4,0x18);
  LZOIsInitialized = lzoCheck(iVar1,pcVar2);
  return LZOIsInitialized;
}
