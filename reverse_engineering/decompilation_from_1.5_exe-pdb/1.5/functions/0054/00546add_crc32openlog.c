/*
 * Entry: 00546add
 * Name: crc32openlog
 * Namespace: Global
 * Signature: void crc32openlog(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl crc32openlog(char *param_1)

{
  errno_t eVar1;
  
  crc32closelog();
  eVar1 = fopen_s((FILE **)&crc32log,param_1,"wt");
  if (eVar1 != 0) {
    crc32logprintf("crc32openlog: error %d when opening \"%s\"\n");
  }
  return;
}
