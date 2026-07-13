
void FUN_008409e0(short *param_1,int *param_2,int *param_3,uint param_4)

{
  short sVar1;
  uint uVar2;
  char cVar3;
  short *psVar4;
  int iVar5;
  uint uVar6;
  
  if (param_4 == 0xffffffff) {
    param_4 = *(uint *)(param_1 + 8);
  }
  *param_2 = 0;
  *param_3 = 0;
  if (*(int *)(param_1 + 8) == 0) {
    return;
  }
  uVar6 = 0;
  if (1 < param_4) {
    uVar2 = *(uint *)(param_1 + 10);
    psVar4 = param_1;
    if (7 < uVar2) {
      psVar4 = *(short **)param_1;
    }
    if ((*psVar4 == 0x2f) || (*psVar4 == 0x5c)) {
      psVar4 = param_1;
      if (7 < uVar2) {
        psVar4 = *(short **)param_1;
      }
      if ((psVar4[1] == 0x2f) || (psVar4[1] == 0x5c)) {
        if (param_4 != 2) {
          psVar4 = param_1;
          if (7 < uVar2) {
            psVar4 = *(short **)param_1;
          }
          cVar3 = FUN_00840bf0(psVar4[2]);
          if (cVar3 != '\0') goto LAB_00840a77;
        }
        uVar6 = 2;
        *param_3 = 2;
        goto LAB_00840a90;
      }
    }
  }
LAB_00840a77:
  psVar4 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    psVar4 = *(short **)param_1;
  }
  if ((*psVar4 == 0x2f) || (*psVar4 == 0x5c)) {
    *param_3 = 1;
    if (param_4 < 2) {
      return;
    }
    uVar6 = 1;
    iVar5 = 0;
    while( true ) {
      psVar4 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar4 = *(short **)param_1;
      }
      sVar1 = *(short *)(iVar5 + 2 + (int)psVar4);
      if ((sVar1 != 0x2f) && (sVar1 != 0x5c)) break;
      uVar6 = uVar6 + 1;
      iVar5 = iVar5 + 2;
      *param_2 = *param_2 + 1;
      if (param_4 <= uVar6) {
        return;
      }
    }
    return;
  }
LAB_00840a90:
  if (uVar6 < param_4) {
    while( true ) {
      psVar4 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar4 = *(short **)param_1;
      }
      if (psVar4[uVar6] == 0x3a) break;
      psVar4 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar4 = *(short **)param_1;
      }
      if ((psVar4[uVar6] == 0x2f) || (psVar4[uVar6] == 0x5c)) break;
      *param_3 = *param_3 + 1;
      uVar6 = uVar6 + 1;
      if (param_4 <= uVar6) break;
    }
  }
  if (uVar6 != param_4) {
    if (7 < *(uint *)(param_1 + 10)) {
      param_1 = *(short **)param_1;
    }
    if (param_1[uVar6] == 0x3a) {
      *param_3 = *param_3 + 1;
      return;
    }
  }
  return;
}

