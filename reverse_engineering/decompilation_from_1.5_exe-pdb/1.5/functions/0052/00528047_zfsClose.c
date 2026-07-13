/*
 * Entry: 00528047
 * Name: zfsClose
 * Namespace: Global
 * Signature: int zfsClose(ZFS_COOKIE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zfsClose(ZFS_COOKIE *param_1)

{
  int iVar1;
  ZFS_COOKIE *unaff_EDI;
  
  fclose((FILE *)param_1->fp);
  iVar1 = delete_cookie(unaff_EDI);
  return iVar1;
}
