
undefined4 FUN_0074e150(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 auStack_18 [8];
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e15e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uStack_10 = param_2;
    FUN_0073a9b0(auStack_18);
    uVar1 = (**(code **)(*local_8 + 0x24))();
  }
  return uVar1;
}

