/*
 * Entry: 005488b7
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, int * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl in(_iobuf *param_1,int *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  char *_Src;
  void *unaff_EBX;
  int iVar4;
  int local_50 [2];
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (binarySave) {
    bVar2 = in_data(4,(long)param_2,unaff_EBX);
  }
  else {
    in_prep();
    sscanf(inCurrent,"%s [%d] =",local_48,local_50);
    pcVar1 = nextLine;
    iVar4 = 0;
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
    if (0 < local_50[0]) {
      do {
        in_prep();
        iVar3 = sscanf(_Src,"%d",param_2);
        inCurrent = nextLine + 2;
        *nextLine = '\r';
        if (iVar3 != 1) {
          return false;
        }
        iVar4 = iVar4 + 1;
        param_2 = param_2 + 1;
      } while (iVar4 < local_50[0]);
    }
    bVar2 = true;
  }
  return bVar2;
}
