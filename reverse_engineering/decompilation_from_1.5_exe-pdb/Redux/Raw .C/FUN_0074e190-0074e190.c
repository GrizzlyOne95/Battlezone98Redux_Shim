
undefined4 FUN_0074e190(void)

{
  undefined4 uVar1;
  undefined1 auStack_14 [4];
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e19e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    FUN_0073a9b0(auStack_14);
    uVar1 = (**(code **)(*local_8 + 0x2c))();
  }
  return uVar1;
}

