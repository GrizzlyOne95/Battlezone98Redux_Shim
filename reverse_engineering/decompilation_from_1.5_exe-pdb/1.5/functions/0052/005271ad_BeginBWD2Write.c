/*
 * Entry: 005271ad
 * Name: BeginBWD2Write
 * Namespace: Global
 * Signature: void * BeginBWD2Write(char * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void * __cdecl BeginBWD2Write(char *param_1,long param_2)

{
  FILE *_File;
  size_t sVar1;
  undefined4 local_20;
  undefined4 local_1c;
  long local_18;
  char *local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14 = param_1;
  local_10 = 0x32445742;
  local_c = 8;
  local_20 = 0x564552;
  local_1c = 0xc;
  local_18 = param_2;
  _File = fopen(param_1,"wb");
  if (_File == (FILE *)0x0) {
    DEBUG_systemWarning("Can\'t open %s for writing");
  }
  else {
    sVar1 = fwrite(&local_10,1,8,_File);
    if ((sVar1 == 8) && (sVar1 = fwrite(&local_20,1,0xc,_File), sVar1 == 0xc)) {
      return _File;
    }
    DEBUG_systemWarning("Error writing %s");
    fclose(_File);
  }
  return (void *)0x0;
}
