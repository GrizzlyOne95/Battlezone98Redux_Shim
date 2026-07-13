/*
 * Entry: 0052805c
 * Name: zfsRefreshCookie
 * Namespace: Global
 * Signature: ZFS_COOKIE * zfsRefreshCookie(ZFS_COOKIE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ZFS_COOKIE * __cdecl zfsRefreshCookie(ZFS_COOKIE *param_1)

{
  ZFS_COOKIE *pZVar1;
  _iobuf *unaff_ESI;
  ZFS_COOKIE *unaff_EDI;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  strcpy_s(local_18,0x10,param_1->fname);
  delete_cookie(unaff_EDI);
  pZVar1 = buildcookie((char *)unaff_EDI,unaff_ESI);
  return pZVar1;
}
