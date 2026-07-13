/*
 * Entry: 005280a3
 * Name: zfsFindRecordInfo
 * Namespace: Global
 * Signature: ZFS_RENTRY * zfsFindRecordInfo(ZFS_COOKIE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ZFS_RENTRY * __cdecl zfsFindRecordInfo(ZFS_COOKIE *param_1,char *param_2)

{
  ZFS_RENTRY *pZVar1;
  char local_2c [36];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  strncpy(local_2c,param_2,0x10);
  pZVar1 = bsearch(local_2c,param_1->entry_table,param_1->num_rentries,0x24,rentry_compare);
  return pZVar1;
}
