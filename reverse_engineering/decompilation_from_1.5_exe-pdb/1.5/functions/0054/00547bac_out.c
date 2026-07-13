/*
 * Entry: 00547bac
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, uchar * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,uchar *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  void *unaff_EDI;
  int iVar2;
  
  if (binarySave) {
    bVar1 = out_data(param_1,2,(long)param_2,unaff_EDI);
  }
  else {
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,param_3);
    iVar2 = 0;
    if (0 < (int)param_3) {
      do {
        fprintf((FILE *)param_1,"%c\r\n",(uint)param_2[iVar2]);
        iVar2 = iVar2 + 1;
      } while (iVar2 < (int)param_3);
    }
    bVar1 = true;
  }
  return bVar1;
}
