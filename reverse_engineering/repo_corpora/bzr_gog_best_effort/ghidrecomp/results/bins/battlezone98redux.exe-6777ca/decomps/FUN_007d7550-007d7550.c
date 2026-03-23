
void FUN_007d7550(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 auStack_408 [160];
  undefined1 local_368 [16];
  undefined1 local_358 [8];
  undefined4 local_350;
  undefined1 *local_34c;
  uint local_348;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862db5;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_348 = 0;
  FUN_007d7a90(local_14);
  local_8 = 1;
  FUN_00574400(3,1);
  local_8._0_1_ = 2;
  if (&stack0x00000000 == (undefined1 *)0x418) {
    local_34c = (undefined1 *)0x0;
  }
  else {
    local_34c = auStack_408;
  }
  FUN_00416430(local_34c,0);
  local_350 = 0;
  uVar2 = FUN_007d97a0(local_368,&stack0x0000000c,&local_350,&stack0x00000010);
  cVar1 = FUN_007d9800(local_358,uVar2,param_2);
  if (cVar1 == '\0') {
    basic_string<>(&DAT_008a1ad8);
    local_348 = local_348 | 1;
    local_8._0_1_ = 1;
    FUN_00417f10();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_007d76f0();
  }
  else {
    GetPolicy(param_1);
    local_348 = local_348 | 1;
    local_8._0_1_ = 1;
    FUN_00417f10();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_007d76f0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

