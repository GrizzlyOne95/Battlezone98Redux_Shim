
uint FUN_0068f030(uint param_1,uint param_2)

{
  uint uVar1;
  
  param_1 = param_1 & 7;
  if (param_1 == 2) {
    uVar1 = param_2 & 0xffffff | 0xa0000000;
  }
  else if (param_1 == 3) {
    uVar1 = param_2 & 0xffffff | 0x60000000;
  }
  else {
    uVar1 = DAT_00920ef8;
    if (param_1 != 5) {
      uVar1 = param_2 & 0xffffff | 0xff000000;
    }
  }
  return uVar1;
}

