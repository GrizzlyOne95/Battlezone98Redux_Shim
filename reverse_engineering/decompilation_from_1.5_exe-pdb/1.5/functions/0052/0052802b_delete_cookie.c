/*
 * Entry: 0052802b
 * Name: delete_cookie
 * Namespace: Global
 * Signature: int delete_cookie(ZFS_COOKIE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl delete_cookie(ZFS_COOKIE *param_1)

{
  void *unaff_EDI;
  
  free(*(void **)((int)unaff_EDI + 0x24));
  free(*(void **)((int)unaff_EDI + 0x28));
  free(unaff_EDI);
  return 1;
}
