
void __fastcall FUN_0074e7d0(int param_1)

{
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  uint uStack_48;
  undefined1 local_38 [16];
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  int *local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bf00;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_48;
  ExceptionList = &local_10;
  *(undefined1 *)(param_1 + 0x120) = 1;
  puStack_4c = (undefined1 *)0x74e80e;
  local_18 = param_1;
  local_1c = (int *)FUN_0074db30();
  local_8 = 0;
  if (local_1c != (int *)0x0) {
    puStack_4c = local_38;
    uStack_50 = 0x74e82a;
    local_20 = FUN_0073bcf0();
    local_24 = (undefined1 *)&uStack_50;
    local_28 = FUN_0073a9b0(&uStack_50);
    (**(code **)(*local_1c + 0x20))();
    ExceptionList = local_10;
    return;
  }
  FUN_0074e86b();
  return;
}

