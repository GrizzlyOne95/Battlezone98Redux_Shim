
void FUN_00701720(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_6c [4];
  undefined1 local_68 [8];
  undefined1 local_60 [12];
  uint local_54;
  uint local_50;
  undefined4 local_4c;
  char local_46;
  char local_45;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856788;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("Sec-WebSocket-Protocol");
  local_8 = 0;
  FUN_006b7490(local_44);
  cVar1 = FUN_0041f890(uVar2);
  local_46 = cVar1 == '\0';
  local_50 = (uint)(byte)local_46;
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (local_46 != '\0') {
    vector<>();
    local_8 = 1;
    basic_string<>("Sec-WebSocket-Protocol");
    local_8._0_1_ = 2;
    cVar1 = FUN_006b74f0(local_2c,local_60);
    local_45 = cVar1 == '\0';
    local_54 = (uint)(byte)local_45;
    local_8 = CONCAT31(local_8._1_3_,1);
    ~basic_string<>();
    if (local_45 == '\0') {
      make_error_code(param_1,0x1b);
      local_8 = 0xffffffff;
      FUN_00704c70();
      goto LAB_0070189b;
    }
    FUN_00423890();
    puVar3 = (undefined4 *)FID_conflict_begin(local_6c);
    local_4c = *puVar3;
    while( true ) {
      uVar4 = FID_conflict_end(local_68);
      cVar1 = FID_conflict_operator__(uVar4);
      if (cVar1 == '\0') break;
      uVar4 = FUN_00422220();
      FUN_006cae50(uVar4);
      FUN_006cc780();
    }
    local_8 = 0xffffffff;
    FUN_00704c70();
  }
  FUN_006ab750();
LAB_0070189b:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

