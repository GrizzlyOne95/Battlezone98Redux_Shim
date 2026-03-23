
void FUN_007c9de0(char *param_1,undefined4 param_2,undefined4 param_3,float param_4,float param_5,
                 undefined4 param_6,undefined4 param_7,uint param_8,undefined4 param_9,
                 undefined4 param_10,undefined4 param_11)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 uVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined1 local_188 [152];
  double local_f0;
  double local_e8;
  undefined4 local_e0;
  undefined4 local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  int *local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  int local_b0;
  void *local_ac;
  int local_a8;
  void *local_a4;
  int *local_a0;
  undefined4 local_9c;
  void *local_98;
  undefined4 local_94;
  int local_90;
  float local_8c;
  float local_88;
  float local_84;
  int *local_80;
  undefined4 *local_7c;
  undefined1 local_60 [28];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086248c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_007d1cc0(param_1,param_2,param_3,param_4,param_5,param_8 | 0x20,param_9,0);
  local_8 = 0;
  *local_7c = cUI_Selectlist::vftable;
  *(undefined1 *)(local_7c + 0x52) = 0;
  local_7c[0x53] = 0xffffffff;
  local_7c[0x54] = 0;
  *(undefined1 *)(local_7c + 0x56) = 1;
  vector<>(uVar2);
  local_8._0_1_ = 1;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  local_7c[0x5d] = param_11;
  local_84 = 0.0;
  local_90 = 0;
  fVar5 = (float10)FUN_00688070(local_7c[0x5d]);
  local_88 = (float)fVar5;
  if (local_88 < 8.0) {
    local_88 = 8.0;
  }
  do {
    local_a8 = size();
    local_f0 = (double)local_a8 + (double)(&DAT_008a2fd0)[-(local_a8 >> 0x1f)];
    local_84 = (float)local_f0 * local_88 + (float)local_7c[2];
    iVar3 = size();
    if (iVar3 != 0) {
      iVar3 = size();
      FUN_004200d0(iVar3 + -1);
      fVar5 = (float10)FUN_007d37d0();
      local_d4 = (float)fVar5;
      cVar1 = FUN_007d2810(local_7c[1],local_d4 + local_88 * 2.0);
      if (cVar1 == '\0') {
        iVar3 = size();
        FUN_004200d0(iVar3 + -1);
        fVar5 = (float10)FUN_007d37d0();
        local_d8 = (float)fVar5;
        local_c4 = local_d8;
        fVar5 = (float10)FUN_00688070(local_7c[0x5d]);
        local_c0 = (float)fVar5;
        local_d0 = (local_c4 + local_c0) - (float)local_7c[2];
        local_8c = ((float)local_7c[4] - local_d0) / (float)local_7c[7];
        local_c8 = param_5 - local_8c;
        local_b0 = size();
        local_e8 = (double)local_b0 + (double)(&DAT_008a2fd0)[-(local_b0 >> 0x1f)];
        local_7c[0x55] = local_c8 / (float)local_e8;
        local_e0 = 0x23;
        basic_string<>(param_1);
        local_8._0_1_ = 8;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c,"pageUp");
        local_a4 = operator_new(0x1ec);
        local_8._0_1_ = 9;
        if (local_a4 == (void *)0x0) {
          local_9c = 0;
        }
        else {
          uVar13 = 0;
          uVar12 = 0;
          uVar11 = 0x20;
          uVar10 = 0x420c0000;
          uVar8 = 0x420c0000;
          fVar7 = param_5 - 70.0;
          fVar6 = param_4 - 35.0;
          puVar9 = local_7c;
          uVar4 = FUN_0041f870(fVar6,fVar7,0x420c0000,0x420c0000,0x20,local_7c,0,0);
          local_9c = FUN_007c2480(uVar4,fVar6,fVar7,uVar8,uVar10,uVar11,puVar9,uVar12,uVar13);
        }
        local_b8 = local_9c;
        local_8._0_1_ = 8;
        local_7c[0x5e] = local_9c;
        FUN_007d3f20(4);
        FUN_007d2870("uparroff.png");
        (**(code **)(*(int *)local_7c[0x5e] + 0x40))("uparrclk.png");
        (**(code **)(*(int *)local_7c[0x5e] + 0x3c))("uparron.png");
        FUN_007c2950(&DAT_008a1ad8);
        FUN_007c23e0(param_6);
        (**(code **)(*(int *)local_7c[0x5e] + 0x24))(0);
        FUN_007d2110(local_7c[0x5e],0);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c,param_1);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c,"pageDn");
        local_ac = operator_new(0x1ec);
        local_8._0_1_ = 10;
        if (local_ac == (void *)0x0) {
          local_94 = 0;
        }
        else {
          uVar13 = 0;
          uVar12 = 0;
          uVar11 = 0x20;
          uVar10 = 0x420c0000;
          uVar8 = 0x420c0000;
          param_5 = param_5 - 35.0;
          param_4 = param_4 - 35.0;
          puVar9 = local_7c;
          uVar4 = FUN_0041f870(param_4,param_5,0x420c0000,0x420c0000,0x20,local_7c,0,0);
          local_94 = FUN_007c2480(uVar4,param_4,param_5,uVar8,uVar10,uVar11,puVar9,uVar12,uVar13);
        }
        local_bc = local_94;
        local_8._0_1_ = 8;
        local_7c[0x5f] = local_94;
        FUN_007d3f20(4);
        FUN_007d2870("dnarroff.png");
        (**(code **)(*(int *)local_7c[0x5f] + 0x40))("dnarrclk.png");
        (**(code **)(*(int *)local_7c[0x5f] + 0x3c))("dnarron.png");
        FUN_007c2950(&DAT_008a1ad8);
        FUN_007c23e0(param_7);
        (**(code **)(*(int *)local_7c[0x5f] + 0x24))(0);
        FUN_007d2110(local_7c[0x5f],0);
        local_8 = CONCAT31(local_8._1_3_,2);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ExceptionList = local_10;
        FUN_0083e885();
        return;
      }
    }
    FUN_006ca050(2,1);
    local_8._0_1_ = 3;
    uVar2 = size();
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(local_188,param_1);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar2);
    GetPolicy(local_44);
    local_8._0_1_ = 4;
    local_98 = operator_new(0x930);
    local_8._0_1_ = 5;
    if (local_98 == (void *)0x0) {
      local_a0 = (int *)0x0;
    }
    else {
      uVar13 = 0;
      uVar12 = 0;
      uVar11 = 0x8408;
      fVar5 = (float10)FUN_00688070(local_7c[0x5d],0x8408,0,0);
      fVar6 = (float)fVar5;
      uVar4 = local_7c[3];
      uVar8 = local_7c[1];
      fVar7 = local_84;
      uVar10 = FUN_0041f870(uVar8,local_84,uVar4,fVar6);
      local_a0 = (int *)FUN_007cc390(uVar10,uVar8,fVar7,uVar4,fVar6,uVar11,uVar12,uVar13);
    }
    local_cc = local_a0;
    local_8._0_1_ = 4;
    local_80 = local_a0;
    uVar2 = FUN_007c19b0();
    FUN_007d3f20((uVar2 & 0xff) + 2);
    (**(code **)(*local_80 + 0x3c))(&DAT_008a1ad8);
    FUN_007cc6b0(local_7c[0x5d]);
    FUN_007cca20(param_10);
    FUN_007cc710(0,0);
    FUN_007d2870("filton.png");
    (**(code **)(*local_80 + 0x24))(0);
    FUN_0041fe40(&local_80);
    local_dc = basic_string<>();
    local_8._0_1_ = 6;
    local_b4 = local_dc;
    FUN_007c9d40(local_dc,0);
    local_8._0_1_ = 7;
    FUN_007cb640(local_60);
    local_8._0_1_ = 6;
    FUN_00430320();
    local_8._0_1_ = 4;
    ~basic_string<>();
    local_90 = local_90 + 1;
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_006b3a50();
  } while( true );
}

