/*
 * Entry: 00548c93
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, VECTOR_2D * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,VECTOR_2D *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  void *in_ECX;
  int iVar3;
  
  if (version < 0x3eb) {
    bVar2 = in(param_1,param_2,param_3);
    return bVar2;
  }
  if (!binarySave) {
    in_prep();
    sscanf(inCurrent,"%*s [%d] =",&stack0xfffffff8);
    pcVar1 = nextLine;
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
    iVar3 = 0;
    if (0 < (int)in_ECX) {
      do {
        bVar2 = in(param_1,&param_2->x,4);
        if ((!bVar2) || (bVar2 = in(param_1,&param_2->z,4), !bVar2)) {
          return false;
        }
        iVar3 = iVar3 + 1;
        param_2 = param_2 + 1;
      } while (iVar3 < (int)in_ECX);
    }
    return true;
  }
  bVar2 = in_data(10,(long)param_2,in_ECX);
  return bVar2;
}
