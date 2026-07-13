/*
 * Entry: 00528919
 * Name: oridedir_countfiles
 * Namespace: Global
 * Signature: int oridedir_countfiles(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl oridedir_countfiles(void)

{
  char cVar1;
  char *pcVar2;
  ZFS_COOKIE *pZVar3;
  long *plVar4;
  HANDLE hFindFile;
  BOOL BVar5;
  int iVar6;
  ZFS_COOKIE **ppZVar7;
  ZIX_PATH_TYPE *_Str;
  ZFS_RENTRY *local_258;
  int local_254;
  int local_250;
  int local_24c;
  _WIN32_FIND_DATAA local_248;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_248.cFileName + 0x44);
  local_24c = 0;
  local_250 = 0;
  if (0 < zix_numpaths) {
    ppZVar7 = &zix_paths[0].cookie;
    do {
      _Str = (ZIX_PATH_TYPE *)(ppZVar7 + -0x42);
      pcVar2 = strstr((char *)_Str,".zfs");
      if (pcVar2 == (char *)0x0) {
        if (ppZVar7[-2] == (ZFS_COOKIE *)0x1) {
          sprintf(local_108,"%s\\*",_Str);
        }
        else if (ppZVar7[-2] == (ZFS_COOKIE *)0x0) {
          cVar1 = CDDriveLetter();
          sprintf(local_108,"%c:\\%s\\*",(int)cVar1,_Str);
        }
        hFindFile = FindFirstFileA(local_108,&local_248);
        if (hFindFile != (HANDLE)0xffffffff) {
          do {
            if ((local_248.cFileName[0] != '.') &&
               (_strlwr(local_248.cFileName), ((byte)local_248.dwFileAttributes & 0x10) == 0)) {
              local_24c = local_24c + 1;
            }
            BVar5 = FindNextFileA(hFindFile,&local_248);
          } while (BVar5 == 1);
          FindClose(hFindFile);
        }
      }
      else {
        pZVar3 = zfsOpen((char *)_Str,0);
        *ppZVar7 = pZVar3;
        zfsGetDirectory(pZVar3,&local_258,&local_254);
        if (0 < local_254) {
          plVar4 = &local_258->flags;
          iVar6 = local_254;
          do {
            if ((*plVar4 & 1) == 0) {
              local_24c = local_24c + 1;
            }
            plVar4 = plVar4 + 9;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
        zfsClose(*ppZVar7);
        *ppZVar7 = (ZFS_COOKIE *)0x0;
      }
      local_250 = local_250 + 1;
      ppZVar7 = ppZVar7 + 0x43;
    } while (local_250 < zix_numpaths);
  }
  return local_24c;
}
