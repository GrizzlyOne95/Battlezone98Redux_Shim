/*
 * Entry: 0052996a
 * Name: zixGetFileHandle
 * Namespace: Global
 * Signature: _iobuf * zixGetFileHandle(char * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

_iobuf * __cdecl zixGetFileHandle(char *param_1,int *param_2,int *param_3)

{
  ZIX_PATH_TYPE *pZVar1;
  char *pcVar2;
  ZFS_COOKIE *pZVar3;
  _iobuf *p_Var4;
  FILE *_File;
  long lVar5;
  char *unaff_ESI;
  ZIX_PATH_TYPE *unaff_EDI;
  char local_244 [120];
  undefined1 local_1cc [180];
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1cc;
  to_zfsname(local_18,param_1);
  *param_3 = 0;
  pZVar1 = locate_file(unaff_EDI->name);
  pcVar2 = resolve_path(unaff_EDI,unaff_ESI);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = strstr(local_118,".zfs");
    if (pcVar2 != (char *)0x0) {
      if (pZVar1->cookie == (ZFS_COOKIE *)0x0) {
        pZVar3 = zfsOpen(local_118,0);
        pZVar1->cookie = pZVar3;
        if (pZVar3 == (ZFS_COOKIE *)0x0) {
          return (_iobuf *)0x0;
        }
      }
      p_Var4 = zfsGetFileHandle(pZVar1->cookie,local_18,param_2);
      return p_Var4;
    }
    sprintf(local_244,"%s\\%s",local_118,local_18);
    _File = fopen(local_244,"rb");
    if (_File != (FILE *)0x0) {
      setvbuf(_File,(char *)0x0,4,0);
      fseek(_File,0,2);
      lVar5 = ftell(_File);
      *param_2 = lVar5;
      fseek(_File,0,0);
      *param_3 = 1;
      return (_iobuf *)_File;
    }
    sprintf(&zfserr,"Couldn\'t open file \"%s\"",local_244);
  }
  return (_iobuf *)0x0;
}
