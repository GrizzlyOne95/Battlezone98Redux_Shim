/*
 * Entry: 00528782
 * Name: oridedir_build_zix_paths
 * Namespace: Global
 * Signature: int oridedir_build_zix_paths(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl oridedir_build_zix_paths(char *param_1)

{
  char cVar1;
  int iVar2;
  HANDLE hFindFile;
  char *pcVar3;
  char *pcVar4;
  BOOL BVar5;
  int iVar6;
  _WIN32_FIND_DATAA local_24c;
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_24c.cFileName + 0x4c);
  hFindFile = FindFirstFileA(param_1,&local_24c);
  if (hFindFile != (HANDLE)0xffffffff) {
    do {
      if (((local_24c.cFileName[0] != '.') ||
          ((local_24c.cFileName[1] != '\0' &&
           ((local_24c.cFileName[1] != '.' || (local_24c.cFileName[2] != '\0')))))) &&
         ((_strlwr(local_24c.cFileName), ((byte)local_24c.dwFileAttributes & 0x10) != 0 ||
          (pcVar3 = strstr(local_24c.cFileName,".zfs"), pcVar3 != (char *)0x0)))) {
        strncpy(local_10c,param_1,0x104);
        pcVar3 = strchr(local_10c,0x2a);
        if (pcVar3 == (char *)0x0) {
          pcVar4 = local_10c;
          do {
            pcVar3 = pcVar4;
            pcVar4 = pcVar3 + 1;
          } while (*pcVar3 != '\0');
        }
        else {
          strncpy(pcVar3,local_24c.cFileName,(int)&local_8 - (int)pcVar3);
          pcVar4 = pcVar3;
          do {
            cVar1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
          } while (cVar1 != '\0');
          pcVar3 = pcVar3 + ((int)pcVar4 - (int)(pcVar3 + 1));
        }
        iVar2 = zix_numpaths;
        pcVar4 = local_10c;
        iVar6 = zix_numpaths * 0x10c - (int)pcVar4;
        do {
          cVar1 = *pcVar4;
          pcVar4[(int)zix_paths + iVar6] = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        zix_paths[zix_numpaths].type = med_dir;
        zix_paths[iVar2].num = 0;
        zix_numpaths = zix_numpaths + 1;
        if (((byte)local_24c.dwFileAttributes & 0x10) != 0) {
          strncat(pcVar3,"\\*",(int)&local_8 - (int)pcVar3);
          oridedir_build_zix_paths(local_10c);
          *pcVar3 = '\0';
        }
      }
      BVar5 = FindNextFileA(hFindFile,&local_24c);
    } while (BVar5 == 1);
    hFindFile = (HANDLE)FindClose(hFindFile);
  }
  return (int)hFindFile;
}
