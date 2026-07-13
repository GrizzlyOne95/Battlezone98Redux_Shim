/*
 * Entry: 0052981e
 * Name: zixGetFileSize
 * Namespace: Global
 * Signature: int zixGetFileSize(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zixGetFileSize(char *param_1)

{
  ZIX_PATH_TYPE *pZVar1;
  char *pcVar2;
  ZFS_COOKIE *pZVar3;
  int iVar4;
  FILE *_File;
  long lVar5;
  char *unaff_ESI;
  ZIX_PATH_TYPE *unaff_EDI;
  char local_244 [300];
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  to_zfsname(local_18,param_1);
  pZVar1 = locate_file(unaff_EDI->name);
  pcVar2 = resolve_path(unaff_EDI,unaff_ESI);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = strstr(local_118,".zfs");
    if (pcVar2 == (char *)0x0) {
      sprintf(local_244,"%s\\%s",local_118,local_18);
      _File = fopen(local_244,"rb");
      if (_File != (FILE *)0x0) {
        setvbuf(_File,(char *)0x0,4,0);
        fseek(_File,0,2);
        lVar5 = ftell(_File);
        fclose(_File);
        return lVar5;
      }
      sprintf(&zfserr,"Couldn\'t open file \"%s\"",local_244);
    }
    else {
      if (pZVar1->cookie == (ZFS_COOKIE *)0x0) {
        pZVar3 = zfsOpen(local_118,0);
        pZVar1->cookie = pZVar3;
        if (pZVar3 == (ZFS_COOKIE *)0x0) {
          return 0;
        }
      }
      iVar4 = zfsFindFileSize(pZVar1->cookie,local_18);
      if (iVar4 != -1) {
        return iVar4;
      }
      sprintf(&zfserr,"Could not find record \"%.16s\" in file \"%.16s\"",local_18,
              pZVar1->cookie->fname);
    }
  }
  return 0;
}
