/*
 * Entry: 0052852e
 * Name: zfsGetFileHandle
 * Namespace: Global
 * Signature: _iobuf * zfsGetFileHandle(ZFS_COOKIE * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_iobuf * __cdecl zfsGetFileHandle(ZFS_COOKIE *param_1,char *param_2,int *param_3)

{
  ZFS_RENTRY *pZVar1;
  _iobuf *p_Var2;
  
  if (param_1->encrypt_key != 0) {
    return (_iobuf *)0x0;
  }
  pZVar1 = zfsFindRecordInfo(param_1,param_2);
  if ((pZVar1->flags & 6) == 0) {
    fseek((FILE *)param_1->fp,pZVar1->offset,0);
    *param_3 = pZVar1->size;
    p_Var2 = param_1->fp;
  }
  else {
    p_Var2 = (_iobuf *)0x0;
  }
  return p_Var2;
}
