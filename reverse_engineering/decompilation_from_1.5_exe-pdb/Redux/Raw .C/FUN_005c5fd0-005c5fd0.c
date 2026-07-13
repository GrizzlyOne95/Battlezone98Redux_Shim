
undefined4 FUN_005c5fd0(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_009181c0 + param_1 * 8);
  }
  return uVar1;
}

