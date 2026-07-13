/*
 * Entry: 00547f92
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, VECTOR_2D * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,VECTOR_2D *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  void *unaff_EDI;
  
  iVar2 = 0;
  if (binarySave) {
    bVar1 = out_data(param_1,10,(long)param_2,unaff_EDI);
  }
  else {
    uVar3 = param_3 >> 3;
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,uVar3);
    if (uVar3 != 0) {
      do {
        bVar1 = out(param_1,&param_2->x,4,"  x");
        if ((!bVar1) || (bVar1 = out(param_1,&param_2->z,4,"  z"), !bVar1)) {
          return false;
        }
        iVar2 = iVar2 + 1;
        param_2 = param_2 + 1;
      } while (iVar2 < (int)uVar3);
    }
    bVar1 = true;
  }
  return bVar1;
}
