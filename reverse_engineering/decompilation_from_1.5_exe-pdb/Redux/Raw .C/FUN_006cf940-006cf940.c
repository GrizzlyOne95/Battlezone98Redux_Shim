
undefined4
FUN_006cf940(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined1 *puStack_4c;
  undefined1 *puStack_48;
  uint uStack_44;
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined1 *local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852d60;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  local_8 = 0;
  puStack_48 = (undefined1 *)0x6cf97e;
  FUN_00421ec0();
  puStack_48 = (undefined1 *)0x6cf985;
  cVar2 = FUN_006b5d40();
  if (cVar2 != '\0') {
    puStack_48 = (undefined1 *)0x6cf994;
    cVar2 = FUN_006d3810();
    if (cVar2 == '\0') {
      puStack_48 = (undefined1 *)0x4;
      puStack_4c = local_30;
      puVar3 = (undefined4 *)make_error_code();
      uVar1 = puVar3[1];
      *param_4 = *puVar3;
      param_4[1] = uVar1;
      puStack_48 = (undefined1 *)0x6cf9be;
      FUN_0068b0a0();
      local_14 = local_14 | 1;
      local_8 = 0xffffffff;
      puStack_48 = (undefined1 *)0x6cf9d6;
      FUN_006ca8c0();
      ExceptionList = local_10;
      return param_1;
    }
  }
  puStack_48 = local_28;
  puStack_4c = (undefined1 *)0x6cf9ea;
  FUN_006db290();
  local_8._0_1_ = 1;
  puStack_48 = (undefined1 *)0x6cf9f6;
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    puStack_48 = (undefined1 *)0x11;
    puStack_4c = local_38;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_4 = *puVar3;
    param_4[1] = uVar1;
    puStack_48 = local_28;
    puStack_4c = (undefined1 *)0x6cfa24;
    shared_ptr<>();
    local_14 = local_14 | 1;
    local_8 = (uint)local_8._1_3_ << 8;
    puStack_48 = (undefined1 *)0x6cfa39;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    puStack_48 = (undefined1 *)0x6cfa48;
    FUN_006ca8c0();
  }
  else {
    local_1c = (undefined1 *)&puStack_4c;
    local_20 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_4c,
                          (shared_ptr<class___ExceptionPtr> *)&param_2);
    FUN_00421ec0();
    FUN_006daee0();
    puStack_48 = (undefined1 *)0x6cfa78;
    puVar3 = (undefined4 *)FUN_006ab750();
    uVar1 = puVar3[1];
    *param_4 = *puVar3;
    param_4[1] = uVar1;
    puStack_48 = local_28;
    puStack_4c = (undefined1 *)0x6cfa91;
    shared_ptr<>();
    local_14 = local_14 | 1;
    local_8 = (uint)local_8._1_3_ << 8;
    puStack_48 = (undefined1 *)0x6cfaa6;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    puStack_48 = (undefined1 *)0x6cfab5;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  return param_1;
}

