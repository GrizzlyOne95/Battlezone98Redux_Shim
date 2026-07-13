
void FUN_00746e80(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_110 [32];
  undefined1 auStack_f0 [160];
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined1 *local_38;
  int *local_34;
  char local_2d;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b823;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_00742cf0(local_14);
  if (cVar1 != '\0') {
    uVar2 = (**(code **)(*local_34 + 0x38))(local_110);
    cVar1 = FUN_0056f780(uVar2);
    if (cVar1 == '\0') {
      FUN_00574400(3,1);
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_3c = (undefined1 *)0x0;
      }
      else {
        local_3c = auStack_f0;
      }
      FUN_004bc590(local_3c,PTR_DAT_008eda34);
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_44 = (undefined1 *)0x0;
      }
      else {
        local_44 = auStack_f0;
      }
      FUN_004bc590(local_44,&DAT_0089a6c4);
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_48 = (undefined1 *)0x0;
      }
      else {
        local_48 = auStack_f0;
      }
      FUN_004bc590(local_48,PTR_DAT_008eda34);
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_38 = (undefined1 *)0x0;
      }
      else {
        local_38 = auStack_f0;
      }
      FUN_0073ba70(local_38,param_1 + 8);
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_40 = (undefined1 *)0x0;
      }
      else {
        local_40 = auStack_f0;
      }
      FUN_004bc590(local_40,PTR_DAT_008eda34);
      local_50 = GetPolicy(local_2c);
      local_8._0_1_ = 1;
      local_4c = local_50;
      local_2d = FUN_007458a0(local_50);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      if (local_2d != '\0') {
        FUN_007476a0();
      }
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

