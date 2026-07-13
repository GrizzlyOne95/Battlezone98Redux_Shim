
void FUN_0076b7a0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_98 [12];
  undefined1 local_8c [8];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_70 [19];
  char local_5d;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085d80b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  if (DAT_00915568 == 0) {
    local_74 = FUN_00820ed0(local_14);
    FUN_00829480();
    FUN_00828790();
    FUN_00827910(&DAT_02cf3000);
    iVar2 = FUN_0081dee0();
    basic_string<>((&PTR_DAT_008fe178)[iVar2]);
    local_8._0_1_ = 2;
    FUN_004bb540(local_70);
    local_8._0_1_ = 3;
    while( true ) {
      local_7c = FUN_004bb570(local_98);
      local_8._0_1_ = 4;
      local_78 = local_7c;
      local_5d = FID_conflict_operator<(local_7c);
      local_8._0_1_ = 3;
      FUN_004bb3b0();
      if (local_5d == '\0') break;
      iVar2 = FUN_00752f10(&stack0x00000004);
      cVar1 = FUN_00427310(iVar2 + 0x3c);
      if (cVar1 != '\0') {
        uVar3 = FUN_00752f10(&stack0x0000001c);
        cVar1 = FUN_00427310(uVar3);
        if (cVar1 != '\0') {
          FUN_004fbb60();
          uVar3 = 0;
          iVar2 = FUN_00752f10(0);
          FUN_00666890(iVar2 + 0x84,uVar3);
          local_8._0_1_ = 5;
          FUN_004fed70(local_44);
          cVar1 = FUN_00767a00(local_2c,local_8c);
          if (cVar1 != '\0') {
            local_84 = FUN_00417fd0(local_5c);
            local_8._0_1_ = 6;
            local_80 = local_84;
            uVar3 = FUN_0041f870();
            FUN_00820e00(uVar3);
            local_8._0_1_ = 5;
            ~basic_string<>();
          }
          FUN_00752f10();
          uVar3 = FUN_0041f870();
          FUN_00827910(uVar3);
          local_8._0_1_ = 3;
          FUN_004180b0();
          break;
        }
      }
      FUN_00732df0();
    }
    local_8._0_1_ = 2;
    FUN_004bb3b0();
    FUN_008282e0(local_74);
    FUN_008283e0();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    local_8 = 0;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

