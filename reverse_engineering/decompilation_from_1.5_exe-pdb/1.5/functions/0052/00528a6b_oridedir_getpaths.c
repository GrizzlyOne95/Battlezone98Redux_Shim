/*
 * Entry: 00528a6b
 * Name: oridedir_getpaths
 * Namespace: Global
 * Signature: int oridedir_getpaths(ZIX_FENTRY_TYPE * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl oridedir_getpaths(ZIX_FENTRY_TYPE *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  ZFS_COOKIE *pZVar3;
  HANDLE hFindFile;
  BOOL BVar4;
  ZFS_COOKIE **ppZVar5;
  ZIX_FENTRY_TYPE *pZVar6;
  int iVar7;
  ZIX_PATH_TYPE *_Str;
  ZFS_RENTRY *local_260;
  int local_25c;
  int local_258;
  ZIX_FENTRY_TYPE *local_254;
  ulong local_250;
  int local_24c;
  _WIN32_FIND_DATAA local_248;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_248.cFileName + 0x3c);
  local_254 = param_1;
  local_24c = 0;
  local_250 = 0;
  if (0 < zix_numpaths) {
    ppZVar5 = &zix_paths[0].cookie;
    do {
      iVar7 = 0;
      _Str = (ZIX_PATH_TYPE *)(ppZVar5 + -0x42);
      pcVar2 = strstr((char *)_Str,".zfs");
      if (pcVar2 == (char *)0x0) {
        if (ppZVar5[-2] == (ZFS_COOKIE *)0x1) {
          sprintf(local_108,"%s\\*",_Str);
        }
        else if (ppZVar5[-2] == (ZFS_COOKIE *)0x0) {
          cVar1 = CDDriveLetter();
          sprintf(local_108,"%c:\\%s\\*.*",(int)cVar1,_Str);
        }
        hFindFile = FindFirstFileA(local_108,&local_248);
        if (hFindFile != (HANDLE)0xffffffff) {
          pZVar6 = local_254 + local_24c;
          do {
            if ((local_248.cFileName[0] != '.') && (((byte)local_248.dwFileAttributes & 0x10) == 0))
            {
              if (local_254 != (ZIX_FENTRY_TYPE *)0x0) {
                if (local_24c < param_2) {
                  pZVar6->paths[0] = local_250;
                  to_zfsname(pZVar6->name,local_248.cFileName);
                }
                else {
                  DEBUG_systemError("ZIX record count overflow.  Try remaking ZIX files.");
                }
              }
              local_24c = local_24c + 1;
              pZVar6 = pZVar6 + 1;
            }
            BVar4 = FindNextFileA(hFindFile,&local_248);
          } while (BVar4 == 1);
          FindClose(hFindFile);
        }
      }
      else {
        pZVar3 = zfsOpen((char *)_Str,0);
        *ppZVar5 = pZVar3;
        zfsGetDirectory(pZVar3,&local_260,&local_25c);
        local_258 = 0;
        if (0 < local_25c) {
          pZVar6 = local_254 + local_24c;
          do {
            if (((*(long *)(local_260->rname + iVar7 + 0x20) & 1) == 0) && (local_24c < param_2)) {
              pZVar6->paths[0] = local_250;
              to_zfsname(pZVar6->name,local_260->rname + iVar7);
              local_24c = local_24c + 1;
              pZVar6 = pZVar6 + 1;
            }
            local_258 = local_258 + 1;
            iVar7 = iVar7 + 0x24;
          } while (local_258 < local_25c);
        }
        zfsClose(*ppZVar5);
        *ppZVar5 = (ZFS_COOKIE *)0x0;
      }
      local_250 = local_250 + 1;
      ppZVar5 = ppZVar5 + 0x43;
    } while ((int)local_250 < zix_numpaths);
  }
  return 1;
}
