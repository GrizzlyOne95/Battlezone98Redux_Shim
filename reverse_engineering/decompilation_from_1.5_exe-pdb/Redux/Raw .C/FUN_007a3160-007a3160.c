
void FUN_007a3160(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  uint uVar4;
  undefined4 uVar5;
  float10 fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f0;
  undefined4 local_1e4;
  undefined4 local_1d8;
  undefined4 local_1d4;
  uint local_1d0;
  char local_1c9;
  int local_1c8;
  undefined1 local_1c4 [24];
  undefined1 local_1ac [24];
  undefined1 local_194 [24];
  undefined1 local_17c [24];
  undefined1 local_164 [24];
  undefined1 local_14c [24];
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008602fc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  vector<>(local_14);
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  FUN_00764790();
  local_1c9 = FUN_00767fe0();
  basic_string<>("All Maps");
  local_8._0_1_ = 3;
  FUN_006cf320(local_74);
  local_8._0_1_ = 2;
  ~basic_string<>();
  iVar1 = FUN_004344a0();
  if (iVar1 != 2) {
    basic_string<>("Strategy");
    local_8._0_1_ = 4;
    FUN_006cf320(local_a4);
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  basic_string<>("Death Match");
  local_8._0_1_ = 5;
  FUN_006cf320(local_134);
  local_8._0_1_ = 2;
  ~basic_string<>();
  basic_string<>(&DAT_0089b420);
  local_8._0_1_ = 6;
  FUN_006cf320(local_d4);
  local_8._0_1_ = 2;
  ~basic_string<>();
  basic_string<>("2 Players");
  local_8._0_1_ = 7;
  FUN_006cf320(local_194);
  local_8._0_1_ = 2;
  ~basic_string<>();
  basic_string<>("3 Players");
  local_8._0_1_ = 8;
  FUN_006cf320(local_104);
  local_8._0_1_ = 2;
  ~basic_string<>();
  basic_string<>("4 Players");
  local_8._0_1_ = 9;
  FUN_006cf320(local_2c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  if (local_1c9 != '\0') {
    basic_string<>("Workshop");
    local_8._0_1_ = 10;
    FUN_006cf320(local_5c);
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  uVar2 = FUN_0081cb40("filters","all_maps");
  basic_string<>(uVar2);
  local_8._0_1_ = 0xb;
  FUN_006cf320(local_8c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  iVar1 = FUN_004344a0();
  if (iVar1 != 2) {
    uVar2 = FUN_0081cb40("filters","strategy");
    basic_string<>(uVar2);
    local_8._0_1_ = 0xc;
    FUN_006cf320(local_bc);
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  uVar2 = FUN_0081cb40("filters","death_match");
  basic_string<>(uVar2);
  local_8._0_1_ = 0xd;
  FUN_006cf320(local_ec);
  local_8._0_1_ = 2;
  ~basic_string<>();
  uVar2 = FUN_0081cb40("filters",&DAT_0089ee64);
  basic_string<>(uVar2);
  local_8._0_1_ = 0xe;
  FUN_006cf320(local_11c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  uVar2 = FUN_0081cb40("filters","2_players");
  basic_string<>(uVar2);
  local_8._0_1_ = 0xf;
  FUN_006cf320(local_14c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  uVar2 = FUN_0081cb40("filters","3_players");
  basic_string<>(uVar2);
  local_8._0_1_ = 0x10;
  FUN_006cf320(local_17c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  uVar2 = FUN_0081cb40("filters","4_players");
  basic_string<>(uVar2);
  local_8._0_1_ = 0x11;
  FUN_006cf320(local_1ac);
  local_8._0_1_ = 2;
  ~basic_string<>();
  if (local_1c9 != '\0') {
    uVar2 = FUN_0081cb40("filters","workshop");
    basic_string<>(uVar2);
    local_8._0_1_ = 0x12;
    FUN_006cf320(local_164);
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  *(undefined4 *)(local_1c8 + 0x3c) = param_2;
  *(undefined1 *)(local_1c8 + 0x48) = 1;
  DAT_00945574 = local_1c8;
  uVar2 = FUN_00764770();
  *(undefined4 *)(local_1c8 + 0x18) = uVar2;
  *(undefined4 *)(local_1c8 + 0x38) = 0xffffffff;
  pvVar3 = operator_new(0x930);
  local_8._0_1_ = 0x13;
  if (pvVar3 == (void *)0x0) {
    local_1fc = 0;
  }
  else {
    local_1fc = FUN_007cc390("Lobby",0x432a0000,0x43480000,0x43a90000,0x422c0000,0x8020,param_1,0);
  }
  local_8._0_1_ = 2;
  *(undefined4 *)(local_1c8 + 0x40) = local_1fc;
  FUN_007d3f20(6);
  (**(code **)(**(int **)(local_1c8 + 0x40) + 0x3c))(&DAT_008a1ad8);
  FUN_007d2110(*(undefined4 *)(local_1c8 + 0x40),0);
  FUN_007cc5c0(0);
  pvVar3 = operator_new(0x294c);
  local_8._0_1_ = 0x14;
  if (pvVar3 == (void *)0x0) {
    local_1f8 = 0;
  }
  else {
    local_1f8 = FUN_007ccb70("chatText",0x42b40000,0x43b40000,0x44138000,0x43020000,0x20,param_1);
  }
  local_8._0_1_ = 2;
  *(undefined4 *)(local_1c8 + 0x44) = local_1f8;
  FUN_007d2110(*(undefined4 *)(local_1c8 + 0x44),0);
  pvVar3 = operator_new(0x180);
  local_8._0_1_ = 0x15;
  if (pvVar3 == (void *)0x0) {
    local_1f0 = 0;
  }
  else {
    local_1f0 = FUN_007c9de0("MapList",0x42e40000,0x430c0000,0x43a78000,0x43520000,FUN_007a3110,
                             FUN_007a3130,0x20,param_1,0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined4 *)(local_1c8 + 0x2c) = local_1f0;
  DAT_00945578 = *(undefined4 *)(local_1c8 + 0x2c);
  FUN_007cb3e0(FUN_007a3150);
  FUN_007d2110(*(undefined4 *)(local_1c8 + 0x2c),0);
  local_1d0 = 0;
  while( true ) {
    uVar4 = FUN_007cb5a0();
    if (uVar4 <= local_1d0) break;
    uVar2 = FUN_007d4300(local_1c4,local_1d0,0);
    local_8._0_1_ = 0x16;
    FUN_006dd7f0(local_44,"MapIcon",uVar2);
    local_8._0_1_ = 0x18;
    ~basic_string<>();
    fVar6 = (float10)FUN_007ca800();
    fVar7 = (float)((double)(int)local_1d0 + (double)(&DAT_008a2fd0)[-((int)local_1d0 >> 0x1f)]) *
            (float)fVar6;
    pvVar3 = operator_new(0x144);
    local_8._0_1_ = 0x19;
    if (pvVar3 == (void *)0x0) {
      local_1d4 = 0;
    }
    else {
      uVar12 = 0;
      uVar2 = *(undefined4 *)(local_1c8 + 0x2c);
      uVar11 = 0x20;
      uVar10 = 0x41600000;
      uVar9 = 0x41600000;
      uVar8 = 0xc1a00000;
      uVar5 = FUN_0041f870(0xc1a00000,fVar7,0x41600000,0x41600000,0x20,uVar2,0);
      local_1d4 = FUN_007d1cc0(uVar5,uVar8,fVar7,uVar9,uVar10,uVar11,uVar2,uVar12);
    }
    local_8._0_1_ = 0x18;
    local_1d8 = local_1d4;
    FUN_007d2110(local_1d4,0);
    FUN_0041fe40(&local_1d8);
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
    local_1d0 = local_1d0 + 1;
  }
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 0x1a;
  if (pvVar3 == (void *)0x0) {
    local_1e4 = 0;
  }
  else {
    local_1e4 = FUN_007d1cc0("MapPreview",0x43b18000,0x40800000,0x43480000,0x43480000,0x20,
                             *(undefined4 *)(local_1c8 + 0x2c),0);
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined4 *)(local_1c8 + 0x1c) = local_1e4;
  FUN_007d2110(*(undefined4 *)(local_1c8 + 0x1c),0);
  FUN_007a4400();
  FUN_007a4260();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

