
void FUN_00702440(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_274 [152];
  undefined1 local_1dc [4];
  undefined1 local_1d8 [4];
  undefined1 local_1d4 [4];
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined1 local_1b4 [8];
  undefined1 local_1ac [4];
  int local_1a8;
  undefined1 local_1a4 [24];
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
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008569c7;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = uVar2;
  basic_string<>(&DAT_008997ec);
  local_8._0_1_ = 1;
  FUN_006b8960(local_54);
  local_8._0_1_ = 0;
  ~basic_string<>(uVar2);
  FUN_00421ec0();
  uVar3 = FUN_006b6010();
  FUN_006b8ad0(uVar3);
  basic_string<>("HTTP/1.1");
  local_8._0_1_ = 2;
  FUN_006b7470(local_6c);
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>("websocket");
  local_8._0_1_ = 3;
  basic_string<>("Upgrade");
  local_8._0_1_ = 4;
  FUN_006b7570(local_84,local_144);
  local_8._0_1_ = 3;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>("Upgrade");
  local_8._0_1_ = 5;
  basic_string<>("Connection");
  local_8._0_1_ = 6;
  FUN_006b7570(local_114,local_9c);
  local_8._0_1_ = 5;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>(&DAT_00899604);
  local_8._0_1_ = 7;
  basic_string<>("Sec-WebSocket-Version");
  local_8._0_1_ = 8;
  FUN_006b7810(local_b4,local_cc);
  local_8._0_1_ = 7;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>(&DAT_00897554);
  local_8._0_1_ = 9;
  puVar4 = local_1a4;
  FUN_00421ec0(puVar4);
  local_1cc = FUN_006b5d60(puVar4);
  local_8._0_1_ = 10;
  local_1bc = local_1cc;
  FUN_006b7810(local_fc,local_1cc);
  local_8._0_1_ = 9;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  cVar1 = FUN_0041fc90();
  if (cVar1 == '\0') {
    FUN_006ca050(2,1);
    local_8 = CONCAT31(local_8._1_3_,0xb);
    FUN_0041fc00(local_1ac);
    FUN_00705490(local_1dc,0);
    uVar3 = get();
    FUN_00574730(local_274,uVar3);
    while( true ) {
      uVar3 = FUN_0041fc60(local_1d4);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      FUN_00705490(local_1d8,0);
      uVar3 = get();
      uVar3 = FUN_004bc590(local_274,&DAT_00892870,uVar3);
      FUN_00574730(uVar3);
    }
    basic_string<>("Sec-WebSocket-Protocol");
    local_8._0_1_ = 0xc;
    local_1d0 = GetPolicy(local_174);
    local_8._0_1_ = 0xd;
    local_1c0 = local_1d0;
    FUN_006b7810(local_12c,local_1d0);
    local_8._0_1_ = 0xc;
    ~basic_string<>();
    local_8._0_1_ = 0xb;
    ~basic_string<>();
    local_8._0_1_ = 0;
    FUN_006b3a50();
  }
  for (local_1a8 = 0; local_1a8 < 4; local_1a8 = local_1a8 + 1) {
    local_1b8 = FUN_00705380();
    FUN_006da2a0(&local_1b8,local_1b4,local_24 + local_1a8 * 4);
  }
  basic_string<>("Sec-WebSocket-Key");
  local_8._0_1_ = 0xe;
  local_1c8 = FUN_006bac90(local_18c,local_24,0x10);
  local_8._0_1_ = 0xf;
  local_1c4 = local_1c8;
  FUN_006b7810(local_15c,local_1c8);
  local_8._0_1_ = 0xe;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  cVar1 = FUN_0044bb90();
  if (cVar1 != '\0') {
    FUN_00706300(local_3c);
    local_8._0_1_ = 0x10;
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      basic_string<>("Sec-WebSocket-Extensions");
      local_8._0_1_ = 0x11;
      FUN_006b7810(local_e4,local_3c);
      local_8._0_1_ = 0x10;
      ~basic_string<>();
    }
    local_8._0_1_ = 0;
    ~basic_string<>();
  }
  FUN_006ab750();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

