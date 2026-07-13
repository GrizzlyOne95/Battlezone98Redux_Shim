/*
 * Entry: 00546d28
 * Name: crc32mission
 * Namespace: Global
 * Signature: ulong crc32mission(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulong __cdecl crc32mission(char *param_1)

{
  char cVar1;
  ulong uVar2;
  HMODULE hModule;
  char *pcVar3;
  int iVar4;
  char **ppcVar5;
  CHAR *lpFilename;
  DWORD nSize;
  char *local_230 [5];
  char *local_21c;
  char *local_218;
  undefined4 local_214;
  char local_210 [96];
  undefined1 local_1b0 [164];
  CHAR local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1b0;
  local_214 = 0;
  local_230[0] = "vxt";
  local_230[1] = "trn";
  local_230[2] = "hgt";
  local_230[3] = "mat";
  local_230[4] = "bzn";
  local_21c = "odf";
  local_218 = "lua";
  crc32logprintf("mission %s\n");
  uVar2 = crc32seed((uchar *)"1.5.2.27 Update 1",0x11,0);
  crc32logprintf("version %08x (%s)\n");
  nSize = 0x104;
  lpFilename = local_10c;
  hModule = GetModuleHandleA((LPCSTR)0x0);
  GetModuleFileNameA(hModule,lpFilename,nSize);
  uVar2 = crc32file(local_10c,uVar2);
  crc32logprintf("executable %08x (%s)\n");
  iVar4 = -(int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)(local_210 + iVar4)] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strchr(local_210,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  uVar2 = crc32game(uVar2);
  ppcVar5 = local_230;
  do {
    sprintf(local_10c,"%s.%s",local_210,*ppcVar5);
    ppcVar5 = ppcVar5 + 1;
    iVar4 = zixIsFileInIndex(local_10c);
    if (iVar4 != 0) {
      uVar2 = crc32zix(local_10c,uVar2);
    }
  } while (*ppcVar5 != (char *)0x0);
  sprintf(local_10c,"%s.dep",local_210);
  iVar4 = zixIsFileInIndex(local_10c);
  if (iVar4 != 0) {
    uVar2 = crc32check(local_10c,uVar2);
  }
  return uVar2;
}
