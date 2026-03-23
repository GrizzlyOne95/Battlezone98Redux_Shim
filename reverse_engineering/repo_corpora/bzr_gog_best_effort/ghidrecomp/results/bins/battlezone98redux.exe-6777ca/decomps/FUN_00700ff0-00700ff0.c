
void FUN_00700ff0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined1 *puVar6;
  undefined1 local_1f0 [8];
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  int *local_1c4;
  char local_1be;
  char local_1bd;
  undefined1 local_1bc [48];
  undefined1 local_18c [24];
  undefined1 local_174 [24];
  undefined1 local_15c [24];
  undefined1 local_144 [24];
  undefined1 local_12c [24];
  undefined1 local_114 [24];
  undefined1 local_fc [24];
  undefined1 local_e4 [24];
  undefined1 local_cc [24];
  undefined1 local_b4 [24];
  undefined1 local_9c [24];
  undefined1 local_84 [24];
  undefined1 local_6c [24];
  undefined1 local_54 [24];
  undefined1 local_3c [24];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008566ba;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("Sec-WebSocket-Key1");
  local_8 = 0;
  puVar6 = local_24;
  uVar3 = FUN_006b7490(local_15c);
  FUN_00705640(uVar3,puVar6);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar2);
  basic_string<>("Sec-WebSocket-Key2");
  local_8 = 1;
  puVar6 = local_20;
  uVar3 = FUN_006b7490(local_3c);
  FUN_00705640(uVar3,puVar6);
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("Sec-WebSocket-Key3");
  local_8 = 2;
  local_1c8 = FUN_006b7490(local_54);
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_1d0 = FUN_004170c0();
  local_1e4 = 8;
  iVar4 = FUN_0041f870(local_1c);
  piVar5 = (int *)_Min_value<>(&local_1e4,&local_1d0);
  uVar3 = FUN_0041f870(iVar4 + *piVar5);
  FUN_006da2a0(uVar3);
  basic_string<>("Sec-WebSocket-Key3");
  local_8 = 3;
  local_1d8 = basic_string<>(local_24,0x10);
  local_8._0_1_ = 4;
  local_1cc = local_1d8;
  local_1e8 = FUN_006bd660(local_1bc,local_1d8);
  local_8._0_1_ = 5;
  local_1e0 = local_1e8;
  FUN_006b7570(local_cc,local_1e8);
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("WebSocket");
  local_8 = 6;
  basic_string<>("Upgrade");
  local_8._0_1_ = 7;
  FUN_006b7570(local_12c,local_fc);
  local_8 = CONCAT31(local_8._1_3_,6);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("Upgrade");
  local_8 = 8;
  basic_string<>("Connection");
  local_8._0_1_ = 9;
  FUN_006b7570(local_84,local_6c);
  local_8 = CONCAT31(local_8._1_3_,8);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("Sec-WebSocket-Origin");
  local_8 = 10;
  FUN_006b7490(local_b4);
  local_1be = FUN_0041f890();
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (local_1be != '\0') {
    basic_string<>("Origin");
    local_8 = 0xb;
    basic_string<>("Sec-WebSocket-Origin");
    local_8._0_1_ = 0xc;
    uVar3 = FUN_006b7490(local_114);
    FUN_006b7570(local_e4,uVar3);
    local_8 = CONCAT31(local_8._1_3_,0xb);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  basic_string<>("Sec-WebSocket-Location");
  local_8 = 0xd;
  FUN_006b7490(local_144);
  local_1bd = FUN_0041f890();
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (local_1bd != '\0') {
    (**(code **)(*local_1c4 + 0x30))(local_1f0,param_2);
    local_8 = 0xe;
    basic_string<>("Sec-WebSocket-Location");
    local_8._0_1_ = 0xf;
    puVar6 = local_18c;
    FUN_00421ec0(puVar6);
    local_1dc = FUN_006b6030(puVar6);
    local_8._0_1_ = 0x10;
    local_1d4 = local_1dc;
    FUN_006b7570(local_174,local_1dc);
    local_8._0_1_ = 0xf;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,0xe);
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    basic_string<>("Sec-WebSocket-Protocol");
    local_8 = 0x11;
    FUN_006b7810(local_9c,param_3);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  FUN_006ab750();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

