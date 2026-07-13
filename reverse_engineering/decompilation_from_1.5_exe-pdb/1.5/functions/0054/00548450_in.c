/*
 * Entry: 00548450
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl in(_iobuf *param_1,char *param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  byte *pbVar5;
  int iVar6;
  bool bVar7;
  byte local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (binarySave) {
    bVar7 = true;
  }
  else {
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    in_prep();
    strncpy((char *)local_1c,inCurrent,(int)pcVar4 - (int)(param_2 + 1));
    pcVar3 = nextLine;
    local_1c[(int)pcVar4 - (int)(param_2 + 1)] = 0;
    pbVar5 = local_1c;
    do {
      bVar2 = *param_2;
      bVar7 = bVar2 < *pbVar5;
      if (bVar2 != *pbVar5) {
LAB_005484c4:
        iVar6 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_005484c9;
      }
      if (bVar2 == 0) break;
      bVar2 = param_2[1];
      bVar7 = bVar2 < pbVar5[1];
      if (bVar2 != pbVar5[1]) goto LAB_005484c4;
      param_2 = param_2 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar2 != 0);
    iVar6 = 0;
LAB_005484c9:
    *nextLine = '\r';
    inCurrent = pcVar3 + 2;
    bVar7 = iVar6 == 0;
  }
  return bVar7;
}
