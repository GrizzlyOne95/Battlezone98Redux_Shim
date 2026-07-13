
undefined4 FUN_0074e720(void)

{
  undefined4 uVar1;
  undefined1 auStack_18 [8];
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e72e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uStack_10 = 0x74e73f;
    uStack_10 = FUN_0041f870();
    FUN_0073a9b0(auStack_18);
    uVar1 = (**(code **)(*local_8 + 0x48))();
  }
  return uVar1;
}

