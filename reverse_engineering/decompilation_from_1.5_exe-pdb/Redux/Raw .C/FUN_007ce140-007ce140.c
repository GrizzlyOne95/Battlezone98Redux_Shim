
void __thiscall
FUN_007ce140(undefined4 *param_1,char param_2,char *param_3,undefined4 param_4,undefined4 param_5,
            float param_6,float param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,
            undefined4 param_11)

{
  uint uVar1;
  undefined4 uVar2;
  void *pvVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 local_3c;
  undefined4 local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008626f8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007ccb70(param_3,param_4,param_5,param_6,param_7,param_10,param_11);
  local_8 = 0;
  *param_1 = cUI_ChatBlock::vftable;
  param_1[0xa56] = 0;
  uVar2 = FUN_007cce90(uVar1);
  param_1[0xa53] = uVar2;
  uVar2 = 0x23;
  uVar12 = 0x1e;
  basic_string<>(param_3);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"pageUp");
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar3 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0x20;
    uVar7 = 0x420c0000;
    uVar6 = 0x41f00000;
    fVar5 = param_7 - 70.0;
    fVar4 = param_6 + 5.0;
    puVar8 = param_1;
    uVar2 = FUN_0041f870(fVar4,fVar5,0x41f00000,0x420c0000,0x20,param_1,0,0,uVar1,uVar2,uVar12);
    local_3c = FUN_007c2480(uVar2,fVar4,fVar5,uVar6,uVar7,uVar9,puVar8,uVar10,uVar11);
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[0xa54] = local_3c;
  FUN_007d3f20(4);
  FUN_007d2870("uparroff.png");
  (**(code **)(*(int *)param_1[0xa54] + 0x40))("uparrclk.png");
  (**(code **)(*(int *)param_1[0xa54] + 0x3c))("uparron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_8);
  if (param_2 == '\0') {
    FUN_007d2110(param_1[0xa54],0);
  }
  else {
    FUN_007d2110(param_1[0xa54],0);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"pageDn");
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar3 == (void *)0x0) {
    local_34 = 0;
  }
  else {
    uVar10 = 0;
    uVar9 = 0;
    uVar7 = 0x20;
    uVar6 = 0x420c0000;
    uVar12 = 0x41f00000;
    param_7 = param_7 - 35.0;
    param_6 = param_6 + 5.0;
    puVar8 = param_1;
    uVar2 = FUN_0041f870(param_6,param_7,0x41f00000,0x420c0000,0x20,param_1,0,0);
    local_34 = FUN_007c2480(uVar2,param_6,param_7,uVar12,uVar6,uVar7,puVar8,uVar9,uVar10);
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[0xa55] = local_34;
  FUN_007d3f20(4);
  FUN_007d2870("dnarroff.png");
  (**(code **)(*(int *)param_1[0xa55] + 0x40))("dnarrclk.png");
  (**(code **)(*(int *)param_1[0xa55] + 0x3c))("dnarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(param_9);
  if (param_2 == '\0') {
    FUN_007d2110(param_1[0xa55],0);
  }
  else {
    FUN_007d2110(param_1[0xa55],0);
  }
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

