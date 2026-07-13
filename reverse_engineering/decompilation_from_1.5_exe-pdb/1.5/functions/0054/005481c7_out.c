/*
 * Entry: 005481c7
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, long64 * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,long64 *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  uint uVar2;
  void *unaff_EDI;
  
  if (binarySave) {
    bVar1 = out_data(param_1,7,(long)param_2,unaff_EDI);
  }
  else {
    uVar2 = param_3 >> 3;
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,uVar2);
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      fprintf((FILE *)param_1,"%.8s\r\n",param_2);
      param_2 = param_2 + 1;
    }
    bVar1 = true;
  }
  return bVar1;
}
