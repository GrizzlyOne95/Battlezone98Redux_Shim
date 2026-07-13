/*
 * Entry: 00547a77
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, void * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,void *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  int iVar2;
  void *unaff_EDI;
  uint uVar3;
  
  if (binarySave) {
    bVar1 = out_data(param_1,0,(long)param_2,unaff_EDI);
  }
  else {
    fprintf((FILE *)param_1,"%s = ",param_4);
    uVar3 = 0;
    if (param_3 != 0) {
      do {
        fprintf((FILE *)param_1,"%02x",(uint)*(byte *)(uVar3 + (int)param_2));
        uVar3 = uVar3 + 1;
      } while (uVar3 < param_3);
    }
    iVar2 = putc(0xd,(FILE *)param_1);
    if ((iVar2 == -1) || (iVar2 = putc(10,(FILE *)param_1), iVar2 == -1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  }
  return bVar1;
}
