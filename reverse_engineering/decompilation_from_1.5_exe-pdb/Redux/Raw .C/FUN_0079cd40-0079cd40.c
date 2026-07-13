
undefined4 FUN_0079cd40(int param_1,undefined2 param_2,undefined1 param_3)

{
  undefined4 uVar1;
  
  if (param_1 == 0x26) {
    FUN_007a3bd0(1);
    uVar1 = 1;
  }
  else if (param_1 == 0x28) {
    FUN_007a3bd0(0xffffffff);
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_007d2330(param_1,param_2,param_3);
  }
  return uVar1;
}

