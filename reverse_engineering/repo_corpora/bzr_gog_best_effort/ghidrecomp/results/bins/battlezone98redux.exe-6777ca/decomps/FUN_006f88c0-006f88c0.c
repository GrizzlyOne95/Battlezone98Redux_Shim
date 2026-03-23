
undefined4 FUN_006f88c0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_64 [8];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  int local_18;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008558c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_1c = 0;
  FUN_0068b0a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  local_20 = param_2;
  switch(param_2) {
  case 0:
    local_11 = FUN_006d3810();
    local_24 = FUN_0070a730(local_4c,&local_11,local_18 + 0x4be0,local_18 + 0x4a50);
    FID_conflict_operator_(local_24);
    FUN_006ca8c0();
    break;
  default:
    shared_ptr<>(local_44);
    local_1c = local_1c | 1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    ExceptionList = local_10;
    return param_1;
  case 7:
    local_12 = FUN_006d3810();
    uVar1 = select_on_container_copy_construction(local_34,*(undefined4 *)(local_18 + 0x4bec));
    local_28 = FUN_0070a860(local_54,&local_12,local_18 + 0x4be0,local_18 + 0x4a50,uVar1);
    FID_conflict_operator_(local_28);
    FUN_006ca8c0();
    break;
  case 8:
    local_13 = FUN_006d3810();
    uVar1 = select_on_container_copy_construction(local_38,*(undefined4 *)(local_18 + 0x4bec));
    local_2c = FUN_0070a960(local_5c,&local_13,local_18 + 0x4be0,local_18 + 0x4a50,uVar1);
    FID_conflict_operator_(local_2c);
    FUN_006ca8c0();
    break;
  case 0xd:
    local_14 = FUN_006d3810();
    uVar1 = select_on_container_copy_construction(local_3c,*(undefined4 *)(local_18 + 0x4bec));
    local_30 = FUN_0070aa60(local_64,&local_14,local_18 + 0x4be0,local_18 + 0x4a50,uVar1);
    FID_conflict_operator_(local_30);
    FUN_006ca8c0();
  }
  uVar1 = *(undefined4 *)(local_18 + 0xa1c);
  FUN_00421ec0(uVar1);
  FUN_00575f40(uVar1);
  shared_ptr<>(local_44);
  local_1c = local_1c | 1;
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

