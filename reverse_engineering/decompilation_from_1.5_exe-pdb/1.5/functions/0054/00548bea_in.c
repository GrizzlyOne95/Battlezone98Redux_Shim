/*
 * Entry: 00548bea
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, VECTOR_3D * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,VECTOR_3D *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  void *in_ECX;
  float *pfVar3;
  int iVar4;
  
  if (binarySave) {
    bVar2 = in_data(9,(long)param_2,in_ECX);
    return bVar2;
  }
  in_prep();
  sscanf(inCurrent,"%*s [%d] =",&stack0xfffffff8);
  pcVar1 = nextLine;
  *nextLine = '\r';
  inCurrent = pcVar1 + 2;
  iVar4 = 0;
  if (0 < (int)in_ECX) {
    pfVar3 = &param_2->z;
    do {
      bVar2 = in(param_1,(float *)(pfVar3 + -2),4);
      if (((!bVar2) || (bVar2 = in(param_1,pfVar3 + -1,4), !bVar2)) ||
         (bVar2 = in(param_1,pfVar3,4), !bVar2)) {
        return false;
      }
      iVar4 = iVar4 + 1;
      pfVar3 = pfVar3 + 3;
    } while (iVar4 < (int)in_ECX);
  }
  return true;
}
