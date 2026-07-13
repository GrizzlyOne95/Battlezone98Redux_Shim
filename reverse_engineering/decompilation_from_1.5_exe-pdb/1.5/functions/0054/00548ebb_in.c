/*
 * Entry: 00548ebb
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, long64 * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,long64 *param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  void *in_ECX;
  char *extraout_EDX;
  char *pcVar4;
  uint uVar5;
  int local_8;
  
  if (binarySave) {
    bVar1 = in_data(7,(long)param_2,in_ECX);
    return bVar1;
  }
  in_prep();
  iVar2 = sscanf(inCurrent,"%*s [%d] =",&stack0xfffffff4);
  pcVar4 = nextLine;
  local_8 = 0;
  *nextLine = '\r';
  inCurrent = pcVar4 + 2;
  if (0 < (int)in_ECX) {
    do {
      in_prep();
      *(undefined4 *)param_2 = 0;
      *(undefined4 *)((int)param_2 + 4) = 0;
      if (*extraout_EDX != '\0') {
        uVar5 = 0;
        pcVar4 = extraout_EDX;
        do {
          if ((pcVar4[uVar5] == '\0') ||
             (iVar3 = isspace((int)pcVar4[uVar5]), pcVar4 = inCurrent, iVar3 != 0)) break;
          *(char *)((int)param_2 + uVar5) = inCurrent[uVar5];
          uVar5 = uVar5 + 1;
        } while (uVar5 < 8);
      }
      pcVar4 = nextLine;
      *nextLine = '\r';
      inCurrent = pcVar4 + 2;
      if (iVar2 != 1) {
        return false;
      }
      local_8 = local_8 + 1;
      param_2 = param_2 + 1;
    } while (local_8 < (int)in_ECX);
  }
  return true;
}
