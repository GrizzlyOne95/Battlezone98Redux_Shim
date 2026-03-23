
/* WARNING: Removing unreachable block (ram,0x0084082b) */

int FUN_008407b0(short *param_1,uint param_2)

{
  uint uVar1;
  short *psVar2;
  int iVar3;
  
  uVar1 = param_2;
  if (param_2 == 2) {
    psVar2 = param_1;
    if (7 < *(uint *)(param_1 + 10)) {
      psVar2 = *(short **)param_1;
    }
    if ((*psVar2 == 0x2f) || (*psVar2 == 0x5c)) {
      psVar2 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar2 = *(short **)param_1;
      }
      if (psVar2[1] == 0x2f) {
        return 0;
      }
      if (psVar2[1] == 0x5c) {
        return 0;
      }
    }
  }
  else if (param_2 == 0) goto code_r0x0084082e;
  psVar2 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    psVar2 = *(short **)param_1;
  }
  if ((psVar2[param_2 - 1] == 0x2f) || (psVar2[param_2 - 1] == 0x5c)) {
    return param_2 - 1;
  }
code_r0x0084082e:
  iVar3 = FUN_00840960(&DAT_00870c04,param_2 - 1,2);
  if (iVar3 == -1) {
    if (uVar1 < 2) {
      return 0;
    }
    param_2 = 0x3a;
    iVar3 = FUN_00841340(&param_2,uVar1 - 2,1);
    if (iVar3 == -1) {
      return 0;
    }
  }
  if (iVar3 == 1) {
    if (7 < *(uint *)(param_1 + 10)) {
      param_1 = *(short **)param_1;
    }
    if ((*param_1 == 0x2f) || (*param_1 == 0x5c)) {
      return 0;
    }
  }
  return iVar3 + 1;
}

