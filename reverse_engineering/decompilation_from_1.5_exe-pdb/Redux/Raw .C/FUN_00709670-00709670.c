
void FUN_00709670(undefined4 *param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined1 *puStack_94;
  code *pcStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  code *pcStack_84;
  undefined1 local_78 [24];
  undefined1 local_60 [8];
  undefined1 local_58 [16];
  error_condition local_48 [8];
  code *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857438;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pcStack_84 = (code *)0x400;
  uStack_88 = 0x7096b0;
  FUN_006d08b0();
  local_38 = *param_1;
  local_34 = param_1[1];
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    pcStack_84 = (code *)0x7096e3;
    FUN_006d1110();
    local_8 = 0;
    if (*(int *)(local_14 + 0xa20) == 0) {
      if (*(int *)(local_14 + 0xa24) == 3) {
        *(undefined4 *)(local_14 + 0xa24) = 4;
      }
      else {
        pcStack_84 = (code *)local_58;
        uStack_88 = 0x70970d;
        puVar3 = (undefined4 *)make_error_code();
        local_38 = *puVar3;
        local_34 = puVar3[1];
      }
    }
    else {
      if (*(int *)(local_14 + 0xa20) == 3) {
        pcStack_84 = (code *)0x400;
        uStack_88 = 0x709750;
        FUN_006d08b0();
        local_8 = 0xffffffff;
        FUN_006d1140();
        ExceptionList = local_10;
        return;
      }
      pcStack_84 = (code *)local_60;
      uStack_88 = 0x709771;
      puVar3 = (undefined4 *)make_error_code();
      local_38 = *puVar3;
      local_34 = puVar3[1];
    }
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_40 = FUN_00713e50;
    local_3c = 0;
    pcStack_84 = (code *)0x709821;
    uStack_88 = FUN_006e1540();
    local_8 = 1;
    pcStack_84 = _1_exref;
    uStack_8c = local_3c;
    pcStack_90 = local_40;
    puStack_94 = local_78;
    local_20 = uStack_88;
    local_1c = uStack_88;
    local_28 = FUN_0070a660();
    local_8._0_1_ = 2;
    local_2c = (undefined1 *)&puStack_94;
    local_24 = local_28;
    local_30 = FUN_0070a6c0(local_28);
    FUN_006ffbc0(1,local_14 + 0xa30,0x4000);
    local_8 = CONCAT31(local_8._1_3_,1);
    ~input_processor<>();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    pcStack_84 = (code *)0x7097a7;
    FUN_006de390();
    pcStack_84 = (code *)0x7097b3;
    bVar2 = std::error_condition::operator==((error_condition *)&local_38,local_48);
    if ((bVar2) && (*(int *)(local_14 + 0xa20) == 3)) {
      pcStack_84 = (code *)0x400;
      uStack_88 = 0x7097de;
      FUN_006d08b0();
    }
    else {
      pcStack_84 = (code *)0x899a88;
      uStack_88 = 0x10;
      uStack_8c = 0x7097f6;
      FUN_006f90a0();
      pcStack_84 = (code *)0x709802;
      FUN_006daf10();
    }
  }
  ExceptionList = local_10;
  return;
}

