/*
 * Entry: 00546b9f
 * Name: crc32zix
 * Namespace: Global
 * Signature: ulong crc32zix(char * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl crc32zix(char *param_1,ulong param_2)

{
  uchar *puVar1;
  ulong local_8;
  
  doSyncTimer();
  puVar1 = zixReadFile(param_1,(int *)&local_8);
  if (puVar1 == (uchar *)0x0) {
    crc32logprintf("%s not found\n");
  }
  else {
    param_2 = crc32seed(puVar1,local_8,param_2);
    zixFree(puVar1);
    zixLocateFile(param_1);
    crc32logprintf("%s %08x (%s)\n");
  }
  return param_2;
}
