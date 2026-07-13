/*
 * Entry: 005280ee
 * Name: zfsFindRecordNum
 * Namespace: Global
 * Signature: int zfsFindRecordNum(ZFS_COOKIE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zfsFindRecordNum(ZFS_COOKIE *param_1,char *param_2)

{
  ZFS_RENTRY *pZVar1;
  
  pZVar1 = zfsFindRecordInfo(param_1,param_2);
  if (pZVar1 != (ZFS_RENTRY *)0x0) {
    return pZVar1->rnum;
  }
  return -1;
}
