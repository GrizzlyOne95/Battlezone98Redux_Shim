
undefined4 FUN_0073a9f0(undefined4 param_1)

{
  uint uVar1;
  undefined1 auStack_bc [164];
  undefined1 *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b3b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xcc) {
    local_18 = (undefined1 *)0x0;
  }
  else {
    local_18 = auStack_bc;
  }
  FUN_0073aab0(local_18);
  GetPolicy(param_1);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10(uVar1);
  ExceptionList = local_10;
  return param_1;
}

