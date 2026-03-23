
undefined4 FUN_0074e6d0(void)

{
  undefined4 uVar1;
  undefined4 uStack_20;
  undefined1 *local_1c;
  undefined1 auStack_18 [8];
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e6de;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uStack_10 = 0x74e6ef;
    uStack_10 = FUN_0041f870();
    local_1c = auStack_18;
    uStack_20 = 0x74e6fc;
    FUN_0073a9b0();
    FUN_0073a9b0(&uStack_20);
    uVar1 = (**(code **)(*local_8 + 0x60))();
  }
  return uVar1;
}

