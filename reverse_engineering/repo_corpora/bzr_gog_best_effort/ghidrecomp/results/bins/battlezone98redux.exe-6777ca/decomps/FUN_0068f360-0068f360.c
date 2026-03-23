
undefined4 FUN_0068f360(int *param_1,int *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar1 = (((param_1[1] - param_2[3]) - 1U & 0x80000000) >> 3 |
          (param_1[1] - param_2[1] & 0x80000000U) >> 2 |
          ((*param_1 - param_2[2]) - 1U & 0x80000000) >> 1 | *param_1 - *param_2 & 0x80000000U) ^
          0x50000000;
  uVar3 = (((param_1[3] - param_2[3]) - 1U & 0x80000000) >> 3 |
          (param_1[3] - param_2[1] & 0x80000000U) >> 2 |
          ((param_1[2] - param_2[2]) - 1U & 0x80000000) >> 1 | param_1[2] - *param_2 & 0x80000000U)
          ^ 0x50000000;
  if ((uVar1 & uVar3) == 0) {
    if (uVar1 == 0 && uVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if ((uVar1 & 0x80000000) != 0) {
        *param_1 = *param_2;
      }
      if ((uVar1 & 0x20000000) != 0) {
        param_1[1] = param_2[1];
      }
      if ((uVar3 & 0x40000000) != 0) {
        param_1[2] = param_2[2];
      }
      if ((uVar3 & 0x10000000) != 0) {
        param_1[3] = param_2[3];
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

