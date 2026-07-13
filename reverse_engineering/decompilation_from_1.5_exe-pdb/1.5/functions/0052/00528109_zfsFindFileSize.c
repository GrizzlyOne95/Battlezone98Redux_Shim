/*
 * Entry: 00528109
 * Name: zfsFindFileSize
 * Namespace: Global
 * Signature: int zfsFindFileSize(ZFS_COOKIE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zfsFindFileSize(ZFS_COOKIE *param_1,char *param_2)

{
  ZFS_RENTRY *pZVar1;
  
  pZVar1 = zfsFindRecordInfo(param_1,param_2);
  if (pZVar1 == (ZFS_RENTRY *)0x0) {
    return -1;
  }
  if ((pZVar1->flags & 6U) != 0) {
    return pZVar1->flags >> 8;
  }
  return pZVar1->size;
}
