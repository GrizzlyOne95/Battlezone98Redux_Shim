/*
 * Entry: 0054881e
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, ushort * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,ushort *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  char *_Src;
  void *unaff_EBX;
  int iVar4;
  int local_c [2];
  
  iVar4 = 0;
  if (binarySave) {
    bVar2 = in_data(3,(long)param_2,unaff_EBX);
  }
  else {
    in_prep();
    sscanf(inCurrent,"%*s [%d] =",local_c);
    pcVar1 = nextLine;
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
    if (0 < local_c[0]) {
      do {
        in_prep();
        iVar3 = sscanf(_Src,"%hu",param_2);
        inCurrent = nextLine + 2;
        *nextLine = '\r';
        if (iVar3 != 1) {
          return false;
        }
        iVar4 = iVar4 + 1;
        param_2 = param_2 + 1;
      } while (iVar4 < local_c[0]);
    }
    bVar2 = true;
  }
  return bVar2;
}
