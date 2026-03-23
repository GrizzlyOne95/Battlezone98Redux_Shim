
undefined4 FUN_0074e670(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 auStack_1c [4];
  undefined4 uStack_18;
  undefined1 local_14 [12];
  int *local_8;
  
  uStack_18 = 0x74e67e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uStack_18 = 0x74e6ba;
    FUN_0073a6b0();
  }
  else {
    FUN_0073a9b0(auStack_1c);
    uVar1 = (**(code **)(*local_8 + 0x78))(local_14);
    FUN_0073a710(uVar1);
  }
  return param_1;
}

