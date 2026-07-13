
void __thiscall
FUN_007c3e30(undefined4 *param_1,char *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  char in_stack_00000040;
  undefined4 uVar6;
  undefined4 uVar7;
  float fVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 local_70;
  undefined4 local_64;
  undefined4 local_5c;
  char *local_58;
  undefined4 local_54;
  char *local_50;
  char *local_4c;
  char *local_48;
  float local_40;
  undefined4 local_38;
  float local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00861f38;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = uVar1;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  local_8._0_1_ = 1;
  *param_1 = cUI_Multiplayer_SettingButton::vftable;
  *(undefined1 *)(param_1 + 0x55) = 1;
  local_4c = "sync_join.png";
  local_50 = "sync_join_over.png";
  local_58 = "sync_join_on.png";
  local_48 = "sync_join_off.png";
  local_38 = 0x42640000;
  local_34 = 338.0;
  local_40 = 20.0;
  if (in_stack_00000040 == '\0') {
    local_4c = "time_limit.png";
    local_50 = "time_limit_over.png";
    local_58 = "time_limit_on.png";
    local_48 = "time_limit_off.png";
    local_38 = 0x424c0000;
    local_34 = 288.0;
    local_40 = 10.0;
  }
  basic_string<>(uVar1);
  local_8._0_1_ = 2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"_bg");
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_64 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0x20;
    uVar7 = 0;
    uVar6 = 0;
    fVar8 = local_34;
    uVar4 = local_38;
    puVar9 = param_1;
    uVar3 = FUN_0041f870(0,0,local_34,local_38,0x20,param_1,0);
    local_64 = FUN_007d1cc0(uVar3,uVar6,uVar7,fVar8,uVar4,uVar10,puVar9,uVar11);
  }
  local_8._0_1_ = 2;
  param_1[0x54] = local_64;
  FUN_007d3f20(2);
  FUN_007d2870(local_4c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"_label");
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_54 = 0;
  }
  else {
    uVar10 = 0;
    uVar7 = 0x8020;
    uVar6 = 0;
    fVar5 = (local_34 - 79.0) + local_40;
    fVar8 = local_34;
    uVar4 = local_38;
    puVar9 = param_1;
    uVar3 = FUN_0041f870(fVar5,0,local_34,local_38,0x8020,param_1,0);
    local_54 = FUN_007cc390(uVar3,fVar5,uVar6,fVar8,uVar4,uVar7,puVar9,uVar10);
  }
  local_8._0_1_ = 2;
  param_1[0x52] = local_54;
  FUN_007d3f20(2);
  (**(code **)(*(int *)param_1[0x52] + 0x3c))(&DAT_008712f4);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"_btnlabel");
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar2 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    uVar10 = 0;
    uVar7 = 0x8020;
    uVar6 = 0;
    fVar8 = local_34;
    uVar4 = local_38;
    puVar9 = param_1;
    uVar3 = FUN_0041f870(local_40,0,local_34,local_38,0x8020,param_1,0);
    local_5c = FUN_007cc390(uVar3,local_40,uVar6,fVar8,uVar4,uVar7,puVar9,uVar10);
  }
  local_8._0_1_ = 2;
  param_1[0x53] = local_5c;
  FUN_007d3f20(4);
  uVar4 = FUN_0041f870();
  uVar4 = FUN_0081cb40("multi_three",uVar4);
  (**(code **)(*(int *)param_1[0x53] + 0x3c))(uVar4);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"_btn");
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar2 == (void *)0x0) {
    local_70 = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar7 = 0x20;
    local_34 = local_34 - 79.0;
    uVar6 = 0;
    uVar3 = 0;
    puVar9 = param_1;
    uVar4 = FUN_0041f870(0,0,local_34,local_38,0x20,param_1,0,0);
    local_70 = FUN_007c2480(uVar4,uVar3,uVar6,local_34,local_38,uVar7,puVar9,uVar10,uVar11);
  }
  local_8._0_1_ = 2;
  param_1[0x51] = local_70;
  FUN_007d3f20(3);
  FUN_007d2870(local_48);
  (**(code **)(*(int *)param_1[0x51] + 0x40))(local_50);
  (**(code **)(*(int *)param_1[0x51] + 0x3c))(local_58);
  FUN_007c23e0(param_9);
  FUN_007c2e60(param_10);
  FUN_007d2110(param_1[0x51],0);
  FUN_007d2110(param_1[0x54],0);
  FUN_007d2110(param_1[0x52],0);
  FUN_007d2110(param_1[0x53],0);
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

