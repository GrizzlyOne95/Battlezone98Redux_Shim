/*
 * Entry: 00528515
 * Name: zfsReadRecord
 * Namespace: Global
 * Signature: void * zfsReadRecord(ZFS_COOKIE * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl zfsReadRecord(ZFS_COOKIE *param_1,char *param_2,int *param_3)

{
  void *pvVar1;
  
  pvVar1 = zfsReadRecordInternal(param_1,param_2,param_3,(void *)0x0,0);
  return pvVar1;
}
