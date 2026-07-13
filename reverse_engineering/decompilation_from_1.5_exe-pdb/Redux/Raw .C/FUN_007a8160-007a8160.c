
void FUN_007a8160(undefined4 param_1,undefined4 param_2,float param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined1 param_7)

{
  undefined4 uVar1;
  void *pvVar2;
  uint uVar3;
  undefined4 uVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 local_150;
  int *local_13c;
  undefined4 local_130;
  int *local_128;
  int *local_124;
  int *local_11c;
  uint local_110;
  int *local_10c;
  undefined1 *local_108;
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [48];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860776;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0073a6b0(local_14);
  vector<>();
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  *local_108 = param_7;
  DAT_00945584 = local_108;
  uVar1 = FUN_00764760();
  *(undefined4 *)(local_108 + 0x18) = uVar1;
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_150 = 0;
  }
  else {
    local_150 = FUN_007c9de0("ChatUserList",param_3,param_4,param_5,param_6,FUN_007a8100,
                             FUN_007a8120,0,param_1,0xff00ff00,0x3f800000);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  *(undefined4 *)(local_108 + 4) = local_150;
  FUN_007d3f20(3);
  DAT_00945580 = *(undefined4 *)(local_108 + 4);
  local_110 = 0;
  while( true ) {
    uVar3 = FUN_007cb5a0();
    if (uVar3 <= local_110) break;
    basic_string<>("chatUser");
    local_8._0_1_ = 5;
    uVar1 = FUN_007d4300(local_74,local_110,0);
    local_8._0_1_ = 6;
    FUN_00449810(uVar1);
    local_8._0_1_ = 5;
    ~basic_string<>();
    FUN_007cabf0(&DAT_008a1ad8,local_110,0);
    fVar5 = (float10)FUN_007ca800();
    fVar6 = (float)((double)(int)local_110 + (double)(&DAT_008a2fd0)[-((int)local_110 >> 0x1f)]) *
            (float)fVar5 + 2.0;
    fVar7 = param_3 - 168.0;
    uVar1 = FUN_007d4300(local_a4,local_110,0);
    local_8._0_1_ = 7;
    FUN_006dd7f0(local_2c,"HostIcon",uVar1);
    local_8._0_1_ = 9;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 10;
    if (pvVar2 == (void *)0x0) {
      local_124 = (int *)0x0;
    }
    else {
      uVar13 = 0;
      uVar1 = *(undefined4 *)(local_108 + 4);
      uVar12 = 0x20;
      uVar11 = 0x41600000;
      uVar10 = 0x41600000;
      fVar8 = fVar7;
      fVar9 = fVar6;
      uVar4 = FUN_0041f870(fVar7,fVar6,0x41600000,0x41600000,0x20,uVar1,0);
      local_124 = (int *)FUN_007d1cc0(uVar4,fVar8,fVar9,uVar10,uVar11,uVar12,uVar1,uVar13);
    }
    local_8._0_1_ = 9;
    local_10c = local_124;
    FUN_007d2110(local_124,0);
    FUN_007d2870("host.png");
    (**(code **)(*local_10c + 0x24))(0);
    FUN_0041fe40(&local_10c);
    uVar1 = FUN_007d4300(local_104,local_110,0);
    local_8._0_1_ = 0xb;
    uVar1 = FUN_006dd7f0(local_d4,"MuteIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 9;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0xc;
    if (pvVar2 == (void *)0x0) {
      local_13c = (int *)0x0;
    }
    else {
      uVar13 = 0;
      uVar1 = *(undefined4 *)(local_108 + 4);
      uVar12 = 0x20;
      uVar11 = 0x41600000;
      uVar10 = 0x41600000;
      fVar8 = fVar6;
      uVar4 = FUN_0041f870(fVar7,fVar6,0x41600000,0x41600000,0x20,uVar1,0);
      local_13c = (int *)FUN_007d1cc0(uVar4,fVar7,fVar8,uVar10,uVar11,uVar12,uVar1,uVar13);
    }
    local_8._0_1_ = 9;
    local_10c = local_13c;
    FUN_007d2110(local_13c,0);
    FUN_007d2870("mute.png");
    (**(code **)(*local_10c + 0x24))(0);
    FUN_0041fe40(&local_10c);
    fVar7 = param_3 - 149.0;
    uVar1 = FUN_007d4300(local_8c,local_110,0);
    local_8._0_1_ = 0xd;
    uVar1 = FUN_006dd7f0(local_ec,"ReadyIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 9;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0xe;
    if (pvVar2 == (void *)0x0) {
      local_11c = (int *)0x0;
    }
    else {
      uVar13 = 0;
      uVar1 = *(undefined4 *)(local_108 + 4);
      uVar12 = 0x20;
      uVar11 = 0x41600000;
      uVar10 = 0x41600000;
      fVar8 = fVar7;
      fVar9 = fVar6;
      uVar4 = FUN_0041f870(fVar7,fVar6,0x41600000,0x41600000,0x20,uVar1,0);
      local_11c = (int *)FUN_007d1cc0(uVar4,fVar8,fVar9,uVar10,uVar11,uVar12,uVar1,uVar13);
    }
    local_8._0_1_ = 9;
    local_10c = local_11c;
    FUN_007d2110(local_11c,0);
    FUN_007d2870("waiting_green.png");
    (**(code **)(*local_10c + 0x24))(0);
    FUN_0041fe40(&local_10c);
    uVar1 = FUN_007d4300(local_bc,local_110,0);
    local_8._0_1_ = 0xf;
    uVar1 = FUN_006dd7f0(local_5c,"WaitingIcon",uVar1);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    local_8._0_1_ = 9;
    ~basic_string<>();
    pvVar2 = operator_new(0x144);
    local_8._0_1_ = 0x10;
    if (pvVar2 == (void *)0x0) {
      local_128 = (int *)0x0;
    }
    else {
      uVar13 = 0;
      uVar1 = *(undefined4 *)(local_108 + 4);
      uVar12 = 0x20;
      uVar11 = 0x41600000;
      uVar10 = 0x41600000;
      uVar4 = FUN_0041f870(fVar7,fVar6,0x41600000,0x41600000,0x20,uVar1,0);
      local_128 = (int *)FUN_007d1cc0(uVar4,fVar7,fVar6,uVar10,uVar11,uVar12,uVar1,uVar13);
    }
    local_8._0_1_ = 9;
    local_10c = local_128;
    FUN_007d2110(local_128,0);
    FUN_007d2870("waiting.png");
    (**(code **)(*local_10c + 0x24))(0);
    FUN_0041fe40(&local_10c);
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    local_110 = local_110 + 1;
  }
  FUN_007cb3e0(FUN_007a8150);
  FUN_007d2110(*(undefined4 *)(local_108 + 4),0);
  pvVar2 = operator_new(0x24);
  local_8 = CONCAT31(local_8._1_3_,0x11);
  if (pvVar2 == (void *)0x0) {
    local_130 = 0;
  }
  else {
    local_130 = FUN_007d0770(param_1,param_3 - 100.0,0x44548000,*(undefined4 *)(local_108 + 4),
                             param_2,FUN_007a8140,0);
  }
  *(undefined4 *)(local_108 + 0x4c) = local_130;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

