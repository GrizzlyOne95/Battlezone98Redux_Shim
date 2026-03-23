
void FUN_007d7970(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_364 [16];
  undefined1 local_354 [8];
  undefined4 local_34c;
  undefined1 local_346;
  undefined1 local_345;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862efb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00416430(param_1,0);
  FUN_007d8300(uVar1);
  local_8 = 0;
  local_34c = 0;
  uVar2 = FUN_007d97a0(local_364,&stack0x0000000c,&local_34c,&stack0x00000010);
  local_346 = FUN_007d9830(local_354,uVar2,param_2);
  local_8 = 0xffffffff;
  local_345 = local_346;
  FUN_007d76f0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

