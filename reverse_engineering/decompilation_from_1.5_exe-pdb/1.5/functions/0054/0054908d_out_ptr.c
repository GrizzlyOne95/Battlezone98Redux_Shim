/*
 * Entry: 0054908d
 * Name: out_ptr
 * Namespace: Global
 * Signature: bool out_ptr(_iobuf * param_1, void * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out_ptr(_iobuf *param_1,void *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  int iVar2;
  void *unaff_EDI;
  
  if (binarySave) {
    bVar1 = out_data(param_1,8,(long)param_2,unaff_EDI);
    return bVar1;
  }
  iVar2 = fprintf((FILE *)param_1,"%s = %p\r\n",param_4,*(undefined4 *)param_2);
  return -1 < iVar2;
}
