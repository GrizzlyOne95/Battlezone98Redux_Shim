
undefined4 __thiscall FUN_006bb4e0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 local_24 [8];
  undefined1 local_1c [4];
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008512a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = param_1;
  if (*(int *)(param_1 + 0x10) == 0) {
    uVar1 = select_on_container_copy_construction
                      (local_1c,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_18 = FUN_006da4d0(local_24,uVar1);
    FID_conflict_operator_(local_18);
    FUN_006ca8c0();
    *(undefined4 *)(local_14 + 0x10) = 1;
    FUN_006ab750();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    make_error_code(param_2,3);
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  return param_2;
}

