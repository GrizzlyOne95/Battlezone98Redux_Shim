
void FUN_00487bd0(void)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int local_1a4 [59];
  undefined1 local_b8 [4];
  undefined1 local_b4 [8];
  undefined4 *local_ac;
  undefined1 local_a8 [52];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848e57;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0048a460(&DAT_0095001c,1,0x40,1);
  local_8 = 0;
  bVar1 = std::ios_base::good((ios_base *)((int)local_1a4 + *(int *)(local_1a4[0] + 4)));
  if (bVar1) {
    puVar3 = (undefined4 *)FUN_0048a6a0(0);
    uVar5 = puVar3[1];
    uVar7 = *puVar3;
    puVar3 = (undefined4 *)FUN_0048a6e0(local_1a4);
    FUN_0048b770(*puVar3,puVar3[1],uVar7,uVar5);
    local_8._0_1_ = 1;
    FUN_0048a570();
    FUN_00426b10(0,0,0);
    local_8._0_1_ = 2;
    Append(local_74);
    vector<>();
    local_8 = CONCAT31(local_8._1_3_,3);
    FUN_00430920(local_b4);
    FUN_0042d8c0(local_a8);
    while( true ) {
      uVar5 = FID_conflict_begin(local_b8);
      cVar2 = FUN_00420f10(uVar5);
      if (cVar2 == '\0') break;
      puVar3 = (undefined4 *)FUN_0042da60();
      basic_string<>(*puVar3);
      local_8._0_1_ = 4;
      uVar8 = 0;
      uVar7 = 0;
      pcVar6 = "current";
      uVar5 = FUN_0041f870("current",0,0);
      uVar5 = FUN_00426cf0(uVar5,pcVar6,uVar7,uVar8);
      basic_string<>(uVar5);
      local_8._0_1_ = 5;
      uVar8 = 0;
      uVar7 = 0;
      pcVar6 = "furthest";
      uVar5 = FUN_0041f870("furthest",0,0);
      uVar5 = FUN_00426cf0(uVar5,pcVar6,uVar7,uVar8);
      basic_string<>(uVar5);
      local_8._0_1_ = 6;
      local_ac = (undefined4 *)FUN_0048a3b0(local_2c);
      uVar5 = FUN_0041f870();
      basic_string<>(uVar5);
      local_8._0_1_ = 7;
      uVar5 = FUN_00482580(local_44,0,10);
      *local_ac = uVar5;
      local_8._0_1_ = 6;
      ~basic_string<>();
      uVar5 = FUN_0041f870();
      basic_string<>(uVar5);
      local_8._0_1_ = 8;
      uVar5 = FUN_00482580(local_5c,0,10);
      local_ac[1] = uVar5;
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      ~basic_string<>();
      local_8._0_1_ = 4;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,3);
      ~basic_string<>();
      FUN_0042da80();
    }
    FUN_004879f0();
    local_8._0_1_ = 2;
    FUN_004284d0();
    local_8._0_1_ = 1;
    FUN_00426bc0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  else {
    puVar3 = (undefined4 *)FUN_0048a3b0(&DAT_0094ffe0);
    *puVar3 = DAT_0094672c[2];
    iVar4 = FUN_0048a3b0(&DAT_0094ffe0);
    *(undefined4 *)(iVar4 + 4) = *DAT_0094672c;
    puVar3 = (undefined4 *)FUN_0048a3b0(&DAT_0094fea8);
    *puVar3 = DAT_0094672c[3];
    iVar4 = FUN_0048a3b0(&DAT_0094fea8);
    *(undefined4 *)(iVar4 + 4) = DAT_0094672c[1];
    puVar3 = (undefined4 *)FUN_0048a3b0(&DAT_0094fef8);
    *puVar3 = DAT_0094672c[4];
    FUN_00487f30();
  }
  local_8 = 0xffffffff;
  FUN_0041d080();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

