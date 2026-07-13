
uint FUN_00432b40(char *param_1)

{
  uint uVar1;
  uint3 uVar2;
  
  if (*param_1 == '<') {
    if (param_1[1] == '<') {
      uVar2 = (uint3)((uint)(param_1 + 2) >> 8);
      if (param_1[2] == '<') {
        uVar1 = CONCAT31(uVar2,1);
      }
      else {
        uVar1 = (uint)uVar2 << 8;
      }
    }
    else {
      uVar1 = (uint)(param_1 + 1) & 0xffffff00;
    }
  }
  else {
    uVar1 = (uint)param_1 & 0xffffff00;
  }
  return uVar1;
}

