
undefined4 FUN_0062a5a0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (0x1ff < param_1)) {
    uVar1 = 0xffffffff;
  }
  else {
    *(undefined4 *)(&DAT_02a174a0 + param_1 * 0x20) = param_2;
    uVar1 = 0;
  }
  return uVar1;
}

