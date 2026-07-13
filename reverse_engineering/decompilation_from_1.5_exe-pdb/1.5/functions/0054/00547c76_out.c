/*
 * Entry: 00547c76
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, ushort * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,ushort *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  void *unaff_EDI;
  
  iVar2 = 0;
  if (binarySave) {
    bVar1 = out_data(param_1,3,(long)param_2,unaff_EDI);
  }
  else {
    uVar3 = param_3 >> 1;
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,uVar3);
    if (uVar3 != 0) {
      do {
        fprintf((FILE *)param_1,"%hu\r\n",(uint)param_2[iVar2]);
        iVar2 = iVar2 + 1;
      } while (iVar2 < (int)uVar3);
    }
    bVar1 = true;
  }
  return bVar1;
}
