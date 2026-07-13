/*
 * Entry: 0052800c
 * Name: zfsAddCompressedRecord
 * Namespace: Global
 * Signature: int zfsAddCompressedRecord(ZFS_COOKIE * param_1, void * param_2, int param_3, long param_4, char * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
zfsAddCompressedRecord
          (ZFS_COOKIE *param_1,void *param_2,int param_3,long param_4,char *param_5,int *param_6)

{
  int iVar1;
  char *unaff_EBP;
  int *unaff_retaddr;
  
  iVar1 = zfsAddRecordInternal
                    (param_2,(void *)param_3,param_4,(long)param_5,unaff_EBP,unaff_retaddr);
  return iVar1;
}
