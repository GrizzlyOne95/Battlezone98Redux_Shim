
undefined4 FUN_006cb5b0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 uStack_44;
  shared_ptr<class___ExceptionPtr> *psStack_40;
  undefined4 *puStack_3c;
  uint uStack_38;
  undefined1 local_34 [8];
  shared_ptr<class___ExceptionPtr> local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852918;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  puStack_3c = (undefined4 *)param_2;
  psStack_40 = local_2c;
  uStack_44 = 0x6cb5ec;
  FUN_006dcb50();
  local_8 = 0;
  puStack_3c = (undefined4 *)0x6cb5fe;
  FUN_00421ec0();
  puStack_3c = (undefined4 *)0x6cb605;
  cVar2 = FUN_006b5d20();
  if (cVar2 == '\0') {
    puStack_3c = (undefined4 *)0x6;
    psStack_40 = (shared_ptr<class___ExceptionPtr> *)local_34;
    uStack_44 = 0x6cb617;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_3 = *puVar3;
    param_3[1] = uVar1;
    puStack_3c = (undefined4 *)0x6cb62f;
    FUN_0068b0a0();
    local_14 = local_14 | 1;
    local_8 = 0xffffffff;
    puStack_3c = (undefined4 *)0x6cb647;
    FUN_006ca8c0();
  }
  else {
    puStack_3c = param_3;
    local_1c = (undefined1 *)&uStack_44;
    local_20 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&uStack_44,local_2c);
    local_24 = FUN_006cf940(param_1);
    local_14 = local_14 | 1;
    local_8 = 0xffffffff;
    puStack_3c = (undefined4 *)0x6cb68b;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  return param_1;
}

