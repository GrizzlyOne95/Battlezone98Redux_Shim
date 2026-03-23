
void FUN_006daf10(undefined4 *param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 *puStack_9c;
  code *pcStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 *puStack_8c;
  code *pcStack_88;
  uint uStack_84;
  undefined1 local_80 [24];
  undefined1 local_68 [8];
  undefined1 *local_60;
  undefined1 local_5c [8];
  undefined4 local_54;
  code *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853940;
  local_10 = ExceptionList;
  uStack_84 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_88 = (code *)0x400;
  puStack_8c = (undefined4 *)0x6daf4e;
  local_14 = uStack_84;
  cVar2 = FUN_006d4590();
  if (cVar2 != '\0') {
    pcStack_88 = (code *)0x898a68;
    puStack_8c = (undefined4 *)0x400;
    uStack_90 = 0x6daf6d;
    FUN_006d08b0();
  }
  pcStack_88 = (code *)0x6daf7b;
  cVar2 = FUN_006ab7d0();
  if (cVar2 != '\0') {
    pcStack_88 = (code *)0x6daf90;
    FUN_00421ec0();
    pcStack_88 = (code *)0x6daf97;
    FUN_006d70d0();
    pcStack_88 = (code *)0x6dafa5;
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
              ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_30 + 0x4a58));
  }
  local_34 = 3;
  pcStack_88 = (code *)0x6dafb4;
  cVar2 = FUN_006ab7d0();
  if (cVar2 != '\0') {
    uVar1 = param_1[1];
    *(undefined4 *)(local_30 + 0x4c28) = *param_1;
    *(undefined4 *)(local_30 + 0x4c2c) = uVar1;
    *(undefined2 *)(local_30 + 0x4bf0) = 0x3ee;
    pcStack_88 = (code *)local_2c;
    puStack_8c = (undefined4 *)0x6dafed;
    pcStack_88 = (code *)FUN_006ab780();
    puStack_8c = (undefined4 *)0x6db002;
    local_3c = pcStack_88;
    FUN_0045e0f0();
    pcStack_88 = (code *)0x6db00a;
    ~basic_string<>();
  }
  if (*(char *)(local_30 + 0x4c30) != '\0') {
    *(undefined4 *)(local_30 + 0x4c34) = 4;
  }
  if (*(int *)(local_30 + 0xa20) == 0) {
    *(undefined4 *)(local_30 + 0xa20) = 3;
    local_34 = 1;
    pcStack_88 = (code *)0x15;
    puStack_8c = (undefined4 *)0x6db04f;
    FUN_006eac90();
    pcStack_88 = (code *)local_68;
    puStack_8c = (undefined4 *)0x6db061;
    cVar2 = FUN_006ab800();
    if (cVar2 != '\0') {
      pcStack_88 = (code *)0x6db070;
      FUN_006ea530();
    }
  }
  else {
    if (*(int *)(local_30 + 0xa20) == 3) {
      pcStack_88 = (code *)0x898e10;
      puStack_8c = (undefined4 *)0x400;
      uStack_90 = 0x6db0ac;
      FUN_006d08b0();
      goto LAB_006db142;
    }
    *(undefined4 *)(local_30 + 0xa20) = 3;
    local_34 = 2;
  }
  local_50 = FUN_006e8f50;
  local_4c = 0;
  pcStack_88 = (code *)local_5c;
  puStack_8c = (undefined4 *)0x6db0cb;
  uStack_90 = FUN_006e1540();
  local_8 = 0;
  pcStack_88 = _1_exref;
  puStack_8c = &local_34;
  uStack_94 = local_4c;
  pcStack_98 = local_50;
  puStack_9c = local_80;
  local_44 = uStack_90;
  local_40 = uStack_90;
  local_48 = FUN_006eace0();
  local_8._0_1_ = 1;
  local_60 = (undefined1 *)&puStack_9c;
  local_38 = local_48;
  local_54 = FUN_006ead40(local_48);
  FUN_006e12f0();
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_88 = (code *)0x6db133;
  ~input_processor<>();
  local_8 = 0xffffffff;
  pcStack_88 = (code *)0x6db142;
  FUN_006ca8c0();
LAB_006db142:
  ExceptionList = local_10;
  uStack_84 = 0x6db157;
  FUN_0083e885();
  return;
}

