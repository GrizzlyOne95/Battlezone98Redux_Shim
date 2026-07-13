/*
 * Entry: 00547afb
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, char * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,char *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  void *unaff_EDI;
  
  if (binarySave) {
    bVar1 = out_data(param_1,2,(long)param_2,unaff_EDI);
    return bVar1;
  }
  fprintf((FILE *)param_1,"%s = %.*s\r\n",param_4,param_3,param_2);
  return true;
}
