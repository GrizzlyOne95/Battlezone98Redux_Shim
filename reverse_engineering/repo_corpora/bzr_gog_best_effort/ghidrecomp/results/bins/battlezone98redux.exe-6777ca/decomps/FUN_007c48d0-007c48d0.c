
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_007c48d0(undefined4 *param_1,undefined4 param_2,char *param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,uint param_14,undefined4 param_15)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_64;
  int *local_60;
  undefined4 local_54;
  undefined4 local_44;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861fd0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007d1cc0(param_3,param_4,param_5,param_6,param_7,param_14 | 0x20,param_15,0);
  local_8 = 0;
  *param_1 = cUI_NumericInput::vftable;
  _DAT_009455e8 = param_1;
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_60 = (int *)0x0;
  }
  else {
    local_60 = (int *)FUN_007cc390("label",0,0,0x42c80000,0x41f00000,0x8020,param_1,0);
  }
  local_8._0_1_ = 0;
  FUN_007cc710(0,0xffffffff);
  (**(code **)(*local_60 + 0x3c))(param_2,uVar1);
  FUN_007d2110(local_60,0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 2;
  if (pvVar2 == (void *)0x0) {
    local_64 = 0;
  }
  else {
    local_64 = FUN_007cc390("value_display",0,0x42200000,0x42c80000,0x41f00000,0x8020,param_1,0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_64;
  FUN_007cc710(0,0xffffffff);
  (**(code **)(*(int *)param_1[0x51] + 0x3c))(&DAT_00873c74);
  FUN_007d2110(param_1[0x51],0);
  basic_string<>(param_3);
  local_8._0_1_ = 3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"oneup");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_6c = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar6 = 0x42b40000;
    uVar4 = 0x428c0000;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0x428c0000,0x42b40000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_6c = FUN_007c2480(uVar3,uVar4,uVar6,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x52] = local_6c;
  FUN_007d3f20(4);
  FUN_007d2870("uparroff.png");
  (**(code **)(*(int *)param_1[0x52] + 0x40))("uparrclk.png");
  (**(code **)(*(int *)param_1[0x52] + 0x3c))("uparron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_8);
  FUN_007d2110(param_1[0x52],0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"onedn");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar2 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar4 = 0x42fa0000;
    uVar6 = 0x428c0000;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0x428c0000,0x42fa0000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_74 = FUN_007c2480(uVar3,uVar6,uVar4,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x53] = local_74;
  FUN_007d3f20(4);
  FUN_007d2870("dnarroff.png");
  (**(code **)(*(int *)param_1[0x53] + 0x40))("dnarrclk.png");
  (**(code **)(*(int *)param_1[0x53] + 0x3c))("dnarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_9);
  FUN_007d2110(param_1[0x53],0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"tenup");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar2 == (void *)0x0) {
    local_70 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar6 = 0x42b40000;
    uVar4 = 0x420c0000;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0x420c0000,0x42b40000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_70 = FUN_007c2480(uVar3,uVar4,uVar6,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x52] = local_70;
  FUN_007d3f20(4);
  FUN_007d2870("uparroff.png");
  (**(code **)(*(int *)param_1[0x52] + 0x40))("uparrclk.png");
  (**(code **)(*(int *)param_1[0x52] + 0x3c))("uparron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_10);
  FUN_007d2110(param_1[0x52],0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"tendn");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 7;
  if (pvVar2 == (void *)0x0) {
    local_78 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar4 = 0x42fa0000;
    uVar6 = 0x420c0000;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0x420c0000,0x42fa0000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_78 = FUN_007c2480(uVar3,uVar6,uVar4,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x53] = local_78;
  FUN_007d3f20(4);
  FUN_007d2870("dnarroff.png");
  (**(code **)(*(int *)param_1[0x53] + 0x40))("dnarrclk.png");
  (**(code **)(*(int *)param_1[0x53] + 0x3c))("dnarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_11);
  FUN_007d2110(param_1[0x53],0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"hundredup");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 8;
  if (pvVar2 == (void *)0x0) {
    local_44 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar6 = 0x42b40000;
    uVar4 = 0;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0,0x42b40000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_44 = FUN_007c2480(uVar3,uVar4,uVar6,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x52] = local_44;
  FUN_007d3f20(4);
  FUN_007d2870("uparroff.png");
  (**(code **)(*(int *)param_1[0x52] + 0x40))("uparrclk.png");
  (**(code **)(*(int *)param_1[0x52] + 0x3c))("uparron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_12);
  FUN_007d2110(param_1[0x52],0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"hundreddn");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 9;
  if (pvVar2 == (void *)0x0) {
    local_54 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar8 = 0x420c0000;
    uVar7 = 0x420c0000;
    uVar4 = 0x42fa0000;
    uVar6 = 0;
    puVar5 = param_1;
    uVar3 = FUN_0041f870(0,0x42fa0000,0x420c0000,0x420c0000,0x20,param_1,0,0);
    local_54 = FUN_007c2480(uVar3,uVar6,uVar4,uVar7,uVar8,uVar9,puVar5,uVar10,uVar11);
  }
  local_8._0_1_ = 3;
  param_1[0x53] = local_54;
  FUN_007d3f20(4);
  FUN_007d2870("dnarroff.png");
  (**(code **)(*(int *)param_1[0x53] + 0x40))("dnarrclk.png");
  (**(code **)(*(int *)param_1[0x53] + 0x3c))("dnarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_13);
  FUN_007d2110(param_1[0x53],0);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

