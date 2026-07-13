/*
 * Entry: 005284f3
 * Name: zfsReadRecordToBuffer
 * Namespace: Global
 * Signature: int zfsReadRecordToBuffer(ZFS_COOKIE * param_1, char * param_2, int * param_3, void * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
zfsReadRecordToBuffer(ZFS_COOKIE *param_1,char *param_2,int *param_3,void *param_4,int param_5)

{
  void *pvVar1;
  
  pvVar1 = zfsReadRecordInternal(param_1,param_2,param_3,param_4,param_5);
  return (uint)(pvVar1 != (void *)0x0);
}
