/*
 * Entry: 00547edf
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, VECTOR_3D * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,VECTOR_3D *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  uint uVar2;
  float *pfVar3;
  void *unaff_EDI;
  int local_8;
  
  if (binarySave) {
    bVar1 = out_data(param_1,9,(long)param_2,unaff_EDI);
  }
  else {
    uVar2 = param_3 / 0xc;
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,uVar2);
    local_8 = 0;
    if (uVar2 != 0) {
      pfVar3 = &param_2->z;
      do {
        bVar1 = out(param_1,(float *)(pfVar3 + -2),4,"  x");
        if (((!bVar1) || (bVar1 = out(param_1,pfVar3 + -1,4,"  y"), !bVar1)) ||
           (bVar1 = out(param_1,pfVar3,4,"  z"), !bVar1)) {
          return false;
        }
        local_8 = local_8 + 1;
        pfVar3 = pfVar3 + 3;
      } while (local_8 < (int)uVar2);
    }
    bVar1 = true;
  }
  return bVar1;
}
