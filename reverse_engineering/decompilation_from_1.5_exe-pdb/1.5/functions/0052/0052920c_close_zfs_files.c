/*
 * Entry: 0052920c
 * Name: close_zfs_files
 * Namespace: Global
 * Signature: void close_zfs_files(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl close_zfs_files(void)

{
  ZFS_COOKIE **ppZVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < zix_numpaths) {
    ppZVar1 = &zix_paths[0].cookie;
    do {
      if (*ppZVar1 != (ZFS_COOKIE *)0x0) {
        zfsClose(*ppZVar1);
        *ppZVar1 = (ZFS_COOKIE *)0x0;
      }
      iVar2 = iVar2 + 1;
      ppZVar1 = ppZVar1 + 0x43;
    } while (iVar2 < zix_numpaths);
  }
  return;
}
