/*
 * Entry: 005278b3
 * Name: zfsCreateFile
 * Namespace: Global
 * Signature: int zfsCreateFile(char * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zfsCreateFile(char *param_1,long param_2)

{
  FILE *pFVar1;
  size_t sVar2;
  undefined1 local_e38 [3604];
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  long local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pFVar1 = fopen(param_1,"rb");
  if (pFVar1 == (FILE *)0x0) {
    pFVar1 = fopen(param_1,"wb");
    if (pFVar1 != (FILE *)0x0) {
      local_14 = 0;
      local_10 = param_2;
      local_24 = 0x5a;
      local_23 = 0x46;
      local_22 = 0x53;
      local_21 = 0x46;
      local_20 = 1;
      local_1c = 0x10;
      local_18 = 100;
      local_c = 0x1c;
      memset(local_e38,0,0xe14);
      sVar2 = fwrite(&local_24,0x1c,1,pFVar1);
      if ((sVar2 != 0) && (sVar2 = fwrite(local_e38,0xe14,1,pFVar1), sVar2 != 0)) {
        fclose(pFVar1);
        return 1;
      }
      sprintf(&zfserr,"Error writing to file \"%s\"",param_1);
      fclose(pFVar1);
      return 0;
    }
    sprintf(&zfserr,"Could not create file \"%s\"",param_1);
  }
  else {
    fclose(pFVar1);
    sprintf(&zfserr,"File \"%s\" already exists",param_1);
  }
  return 0;
}
