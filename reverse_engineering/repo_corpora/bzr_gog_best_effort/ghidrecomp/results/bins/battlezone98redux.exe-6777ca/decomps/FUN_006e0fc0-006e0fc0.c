
undefined4 * FUN_006e0fc0(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 auStack_60 [4];
  undefined4 uStack_5c;
  undefined1 *puStack_58;
  undefined1 *puStack_54;
  undefined1 *puStack_50;
  char *pcStack_4c;
  uint uStack_48;
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00853e98;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_4c = "transport::asio::init";
  puStack_50 = (undefined1 *)0x400;
  puStack_54 = (undefined1 *)0x6e1004;
  FUN_006d08b0();
  local_18 = (undefined1 *)&puStack_50;
  puStack_58 = (undefined1 *)&puStack_50;
  puStack_54 = &stack0x00000008;
  uStack_5c = 0x6e1016;
  local_1c = FUN_006dcc30();
  puStack_54 = local_3c;
  puStack_58 = (undefined1 *)0x6e1028;
  FUN_006bb8b0();
  pcStack_4c = (char *)0x6e1030;
  FUN_006ab750();
  pcStack_4c = *(char **)(local_14 + 0x48);
  puStack_50 = local_44;
  puStack_54 = (undefined1 *)0x6e1043;
  FUN_00421ec0();
  puStack_54 = (undefined1 *)0x6e104a;
  puVar2 = (undefined4 *)FUN_006e4a60();
  local_34 = *puVar2;
  local_30 = puVar2[1];
  pcStack_4c = (char *)0x6e105d;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_20 = auStack_60;
    local_24 = function<>(local_14 + 0x18);
    FUN_00421ec0();
    FUN_006e49a0();
    local_28 = auStack_60;
    local_2c = function<>(local_14 + 0x30);
    FUN_00421ec0();
    FUN_006e4a00();
    pcStack_4c = (char *)0x6e10dc;
    FUN_006ab750();
    local_8 = 0xffffffff;
    pcStack_4c = (char *)0x6e10eb;
    FUN_006ca8c0();
  }
  else {
    *param_1 = local_34;
    param_1[1] = local_30;
    local_8 = 0xffffffff;
    pcStack_4c = (char *)0x6e1081;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  return param_1;
}

