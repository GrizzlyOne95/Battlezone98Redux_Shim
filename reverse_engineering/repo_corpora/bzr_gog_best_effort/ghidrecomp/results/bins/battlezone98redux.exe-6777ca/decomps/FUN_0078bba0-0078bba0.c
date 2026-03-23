
void __thiscall FUN_0078bba0(undefined4 *param_1,int param_2)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  void *pvVar4;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  uint local_90;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_8c;
  undefined4 local_58;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ea50;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0();
  local_8 = 0;
  *param_1 = cUI_Loading::vftable;
  *(undefined1 *)((int)param_1 + 0x156) = 0;
  *(undefined1 *)((int)param_1 + 0x155) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (uint)*(byte *)((int)param_1 + 0x155);
  local_90 = (uint)*(byte *)(param_1 + 0x55);
  local_94 = 0x78bc27;
  FUN_007d4530();
  DAT_0094550c = param_1;
  if (param_2 != 0) {
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x78bc43;
    FUN_007c9170();
  }
  DAT_00918328 = 0;
  FUN_007d22b0();
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x78bc5f;
  FUN_007d3f20();
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x78bc6d;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_9c,local_2c);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xffffff60,local_2c);
  iVar3 = FUN_004880e0();
  cVar1 = FUN_00488d80();
  if (cVar1 != '\0') {
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar3 + 0xb0);
    local_90 = 0x78bcda;
    cVar1 = operator!=<>();
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x55) = 0;
      *(undefined1 *)((int)param_1 + 0x155) = 0x33;
      *(undefined1 *)((int)param_1 + 0x156) = 0x66;
      FUN_0041f870();
      pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0x78bd19;
      FUN_007d2870();
      goto LAB_0078be41;
    }
  }
  pbStack_8c = local_2c;
  local_90 = 0x78bd2c;
  cVar1 = FUN_00427310();
  if (cVar1 == '\0') {
    pbStack_8c = local_2c;
    local_90 = 0x78bd7c;
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
      pbStack_8c = local_2c;
      local_90 = 0x78bdcd;
      cVar1 = FUN_00427310();
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x55) = 0;
        *(undefined1 *)((int)param_1 + 0x155) = 0xff;
        *(undefined1 *)((int)param_1 + 0x156) = 0;
        pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )0x78be41;
        FUN_007d2870();
      }
      else {
        *(undefined1 *)(param_1 + 0x55) = 0xff;
        *(undefined1 *)((int)param_1 + 0x155) = 0xcc;
        *(undefined1 *)((int)param_1 + 0x156) = 0;
        pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )0x78be0b;
        FUN_007d2870();
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x55) = 0;
      *(undefined1 *)((int)param_1 + 0x155) = 0;
      *(undefined1 *)((int)param_1 + 0x156) = 0xff;
      pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0x78bdba;
      FUN_007d2870();
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x55) = 0xff;
    *(undefined1 *)((int)param_1 + 0x155) = 0;
    *(undefined1 *)((int)param_1 + 0x156) = 0;
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x78bd69;
    FUN_007d2870();
  }
LAB_0078be41:
  param_1[0x52] = 0;
  iVar3 = FUN_00572a70();
  if (iVar3 != 0) {
    *(undefined1 *)(param_1 + 0x55) = 0x99;
    *(undefined1 *)((int)param_1 + 0x155) = 0;
    *(undefined1 *)((int)param_1 + 0x156) = 0xff;
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x78be84;
    pvVar4 = operator_new(0x930);
    local_8._0_1_ = 2;
    if (pvVar4 == (void *)0x0) {
      local_58 = 0;
    }
    else {
      local_90 = 0x820;
      local_94 = 0x422c0000;
      local_98 = 0x43c80000;
      local_9c = 0x42000000;
      pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   param_1;
      local_58 = FUN_007cc390("AdditionalInfo");
    }
    local_8._0_1_ = 1;
    param_1[0x52] = local_58;
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 param_1[0x52];
    local_90 = 0x78bf26;
    FUN_007d2110();
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x78bf31;
    pvVar4 = operator_new(0x930);
    local_8._0_1_ = 3;
    if (pvVar4 == (void *)0x0) {
      local_44 = 0;
    }
    else {
      local_90 = 0x820;
      local_94 = 0x422c0000;
      local_98 = 0x43c80000;
      local_9c = 0x42960000;
      pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   param_1;
      local_44 = FUN_007cc390(&DAT_0089dc14);
    }
    local_8._0_1_ = 1;
    param_1[0x53] = local_44;
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 param_1[0x53];
    local_90 = 0x78bfd3;
    FUN_007d2110();
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x78bfde;
    pvVar4 = operator_new(0x930);
    local_8._0_1_ = 4;
    if (pvVar4 == (void *)0x0) {
      local_38 = 0;
    }
    else {
      local_90 = 0x20;
      local_94 = 0x422c0000;
      local_98 = 0x43c80000;
      local_9c = 0x44668000;
      pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   param_1;
      local_38 = FUN_007cc390("TimeRemaining");
    }
    local_8 = CONCAT31(local_8._1_3_,1);
    param_1[0x54] = local_38;
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0
    ;
    local_90 = 0x78c07b;
    FUN_007cc710();
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 param_1[0x54];
    local_90 = 0x78c08f;
    FUN_007d2110();
  }
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x78c09a;
  pvVar4 = operator_new(0x150);
  local_8._0_1_ = 5;
  if (pvVar4 == (void *)0x0) {
    local_48 = 0;
  }
  else {
    pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0
    ;
    local_90 = 0x41900000;
    local_94 = 0x4455c000;
    local_98 = 0x4483e000;
    local_9c = 0x43948000;
    local_48 = FUN_007c9a10();
  }
  local_8._0_1_ = 1;
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x78c11b;
  FUN_005df1f0();
  pbStack_8c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_48;
  local_90 = 0x78c129;
  FUN_007d2110();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

