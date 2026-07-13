
uint FUN_008413f0(short *param_1,uint param_2)

{
  uint uVar1;
  short *psVar2;
  uint uVar3;
  
  if (2 < param_2) {
    psVar2 = param_1;
    if (7 < *(uint *)(param_1 + 10)) {
      psVar2 = *(short **)param_1;
    }
    if (psVar2[1] == 0x3a) {
      psVar2 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar2 = *(short **)param_1;
      }
      if ((psVar2[2] == 0x2f) || (psVar2[2] == 0x5c)) {
        return 2;
      }
    }
  }
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
        return 0xffffffff;
      }
      if (psVar2[1] == 0x5c) {
        return 0xffffffff;
      }
    }
  }
  else {
    if (4 < param_2) {
      uVar3 = *(uint *)(param_1 + 10);
      psVar2 = param_1;
      if (7 < uVar3) {
        psVar2 = *(short **)param_1;
      }
      if ((*psVar2 == 0x2f) || (*psVar2 == 0x5c)) {
        psVar2 = param_1;
        if (7 < uVar3) {
          psVar2 = *(short **)param_1;
        }
        if ((psVar2[1] == 0x2f) || (psVar2[1] == 0x5c)) {
          psVar2 = param_1;
          if (7 < uVar3) {
            psVar2 = *(short **)param_1;
          }
          if (psVar2[2] == 0x3f) {
            psVar2 = param_1;
            if (7 < uVar3) {
              psVar2 = *(short **)param_1;
            }
            if ((psVar2[3] == 0x2f) || (psVar2[3] == 0x5c)) {
              uVar1 = FUN_00840890(&DAT_00870c04,4);
              uVar3 = 0xffffffff;
              if (uVar1 < param_2) {
                uVar3 = uVar1;
              }
              return uVar3;
            }
          }
        }
      }
    }
    if (3 < param_2) {
      uVar3 = *(uint *)(param_1 + 10);
      psVar2 = param_1;
      if (7 < uVar3) {
        psVar2 = *(short **)param_1;
      }
      if ((*psVar2 == 0x2f) || (*psVar2 == 0x5c)) {
        psVar2 = param_1;
        if (7 < uVar3) {
          psVar2 = *(short **)param_1;
        }
        if ((psVar2[1] == 0x2f) || (psVar2[1] == 0x5c)) {
          psVar2 = param_1;
          if (7 < uVar3) {
            psVar2 = *(short **)param_1;
          }
          if ((psVar2[2] != 0x2f) && (psVar2[2] != 0x5c)) {
            uVar1 = FUN_00840890(&DAT_00870c04,2);
            uVar3 = 0xffffffff;
            if (uVar1 < param_2) {
              uVar3 = uVar1;
            }
            return uVar3;
          }
        }
      }
    }
    if (param_2 == 0) {
      return 0xffffffff;
    }
  }
  if (7 < *(uint *)(param_1 + 10)) {
    param_1 = *(short **)param_1;
  }
  if ((*param_1 != 0x2f) && (*param_1 != 0x5c)) {
    return 0xffffffff;
  }
  return 0;
}

