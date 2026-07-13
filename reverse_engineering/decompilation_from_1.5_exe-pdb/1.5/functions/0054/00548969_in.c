/*
 * Entry: 00548969
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, long * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,long *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  void *in_ECX;
  char *_Src;
  int iVar4;
  
  if (binarySave) {
    bVar2 = in_data(4,(long)param_2,in_ECX);
    return bVar2;
  }
  in_prep();
  sscanf(inCurrent,"%*s [%d] =",&stack0xfffffff4);
  pcVar1 = nextLine;
  iVar4 = 0;
  *nextLine = '\r';
  inCurrent = pcVar1 + 2;
  if (0 < (int)in_ECX) {
    do {
      in_prep();
      iVar3 = sscanf(_Src,"%ld",param_2);
      inCurrent = nextLine + 2;
      *nextLine = '\r';
      if (iVar3 != 1) {
        return false;
      }
      iVar4 = iVar4 + 1;
      param_2 = param_2 + 1;
    } while (iVar4 < (int)in_ECX);
  }
  return true;
}
