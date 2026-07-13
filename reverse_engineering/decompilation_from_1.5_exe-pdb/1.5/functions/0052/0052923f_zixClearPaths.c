/*
 * Entry: 0052923f
 * Name: zixClearPaths
 * Namespace: Global
 * Signature: void zixClearPaths(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl zixClearPaths(void)

{
  free(fentry);
  fentry = (ZIX_FENTRY_TYPE *)0x0;
  num_fentries = 0;
  close_zfs_files();
  return;
}
