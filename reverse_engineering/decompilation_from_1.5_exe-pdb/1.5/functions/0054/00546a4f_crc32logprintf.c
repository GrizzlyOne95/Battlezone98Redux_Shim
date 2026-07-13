/*
 * Entry: 00546a4f
 * Name: crc32logprintf
 * Namespace: Global
 * Signature: void crc32logprintf(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl crc32logprintf(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char local_1008 [4096];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (crc32log != (_iobuf *)0x0) {
    _vsnprintf_s(local_1008,0x1000,0x1000,param_1,&stack0x00000008);
    pcVar2 = local_1008;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    fwrite(local_1008,1,(int)pcVar2 - (int)(local_1008 + 1),(FILE *)crc32log);
  }
  return;
}
