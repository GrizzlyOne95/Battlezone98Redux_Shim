
undefined4 * __thiscall FUN_00793ca0(undefined4 *param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  void *pvVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  char *pcVar5;
  int iVar6;
  bool bVar7;
  undefined4 local_c8;
  undefined4 local_c4;
  char *local_c0;
  int iVar8;
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_24;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f084;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0();
  local_8 = 0;
  *param_1 = cUI_MissionSuccess::vftable;
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  param_1[0x54] = 0;
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  param_1[0x4e] = param_2;
  FUN_007659b0();
  DAT_00945544 = param_1;
  FUN_007d3f20();
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar3 == (void *)0x0) {
    local_28 = 0;
  }
  else {
    local_c0 = (char *)0x44870000;
    local_c4 = 0x44b40000;
    local_c8 = 0;
    local_28 = FUN_007d1cc0();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x51] = local_28;
  FUN_007d3f20();
  FUN_007d2110();
  bVar1 = false;
  bVar7 = false;
  if (DAT_00945548 != '\0') goto LAB_00793f6f;
  if (DAT_00918314 == 0) {
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00482850();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0xffffff34,pbVar4);
    FUN_004880e0();
    cVar2 = FUN_0041f890();
    if (cVar2 == '\0') {
      iVar8 = 0x2e;
      pcVar5 = (char *)FUN_0041f870();
      pcVar5 = strrchr(pcVar5,iVar8);
      iVar8 = _stricmp(pcVar5,".ogv");
      bVar7 = iVar8 == 0;
      if (!bVar7) {
        FUN_0041f870();
        FUN_007d2870();
      }
      bVar1 = true;
    }
  }
  FUN_00482850();
  cVar2 = FUN_00427310();
  if (cVar2 == '\0') {
LAB_00793f15:
    FUN_00482850();
    cVar2 = FUN_00427310();
    if (cVar2 == '\0') goto LAB_00793f6f;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_c8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094fe78);
    iVar8 = FUN_004885d0();
    FUN_00482850();
    iVar6 = FUN_004888b0();
    if (iVar6 + 1 != iVar8) goto LAB_00793f6f;
  }
  else {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_c8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094ffe0);
    iVar8 = FUN_004885d0();
    FUN_00482850();
    iVar6 = FUN_004888b0();
    if (iVar6 + 1 != iVar8) goto LAB_00793f15;
  }
  bVar1 = true;
LAB_00793f6f:
  if (bVar1) {
    FUN_0081cb40();
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 2;
    if (pvVar3 == (void *)0x0) {
      local_30 = 0;
    }
    else {
      local_c0 = (char *)0xa6;
      local_c4 = 0x429a0000;
      local_c8 = 0x43ab0000;
      local_30 = FUN_007c2480();
    }
    local_8._0_1_ = 0;
    param_1[0x54] = local_30;
    FUN_007d2870();
    (**(code **)(*(int *)param_1[0x54] + 0x40))();
    (**(code **)(*(int *)param_1[0x54] + 0x3c))();
    local_c0 = "h@*y";
    FUN_007c2950();
    local_c0 = "j";
    FUN_007c23e0();
    local_c0 = (char *)param_1[0x54];
    local_c4 = 0x7940cc;
    FUN_007d2110();
    local_c0 = (char *)0x7940d6;
    local_c0 = (char *)FUN_00482850();
    local_c4 = 0x7940dc;
    cVar2 = FUN_00427310();
    if (cVar2 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xffffff30,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094ffe0);
      iVar8 = FUN_004885d0();
      FUN_00482850();
      local_c0 = (char *)0x794118;
      iVar6 = FUN_004888b0();
      if (iVar6 + 1 == iVar8) {
        FUN_00793070();
        local_c0 = (char *)0x79413a;
        pvVar3 = operator_new(0x144);
        local_8._0_1_ = 3;
        if (pvVar3 == (void *)0x0) {
          local_24 = 0;
        }
        else {
          local_c4 = 0x101;
          local_c8 = 0x44870000;
          local_c0 = (char *)param_1;
          local_24 = FUN_007d1cc0("movie");
        }
        local_8 = (uint)local_8._1_3_ << 8;
        param_1[0x53] = local_24;
        local_c0 = (char *)0x7941d8;
        FUN_007d3f20();
        local_c0 = (char *)0x7941e8;
        FUN_0078c480();
        FUN_0081dee0();
        local_c0 = "outro.ogv";
        local_c4 = 0x794208;
        FUN_007d3850();
        local_c0 = "j";
        FUN_007d3dd0();
        local_c0 = (char *)param_1[0x53];
        local_c4 = 0x794232;
        FUN_007d2110();
        ExceptionList = local_10;
        return param_1;
      }
    }
    local_c0 = (char *)0x794241;
    local_c0 = (char *)FUN_00482850();
    local_c4 = 0x794247;
    cVar2 = FUN_00427310();
    if (cVar2 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xffffff30,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fe78);
      iVar8 = FUN_004885d0();
      FUN_00482850();
      local_c0 = (char *)0x794286;
      iVar6 = FUN_004888b0();
      if (iVar6 + 1 == iVar8) {
        FUN_00793070();
        local_c0 = (char *)0x7942a8;
        pvVar3 = operator_new(0x144);
        local_8._0_1_ = 4;
        if (pvVar3 == (void *)0x0) {
          local_34 = 0;
        }
        else {
          local_c4 = 0x101;
          local_c8 = 0x44870000;
          local_c0 = (char *)param_1;
          local_34 = FUN_007d1cc0("movie");
        }
        local_8 = (uint)local_8._1_3_ << 8;
        param_1[0x53] = local_34;
        local_c0 = (char *)0x794346;
        FUN_007d3f20();
        local_c0 = "j";
        FUN_0078c480();
        local_c0 = "01TRO_OutroV1.ogv";
        local_c4 = 0x79436b;
        FUN_007d3850();
        local_c0 = "j";
        FUN_007d3dd0();
        local_c0 = (char *)param_1[0x53];
        local_c4 = 0x794395;
        FUN_007d2110();
        ExceptionList = local_10;
        return param_1;
      }
    }
    if (bVar7) {
      local_c0 = (char *)0x7943b4;
      pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00482850();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xffffff2c,pbVar4);
      FUN_004880e0();
      FUN_00793070();
      local_c0 = (char *)0x7943ef;
      pvVar3 = operator_new(0x144);
      local_8._0_1_ = 5;
      if (pvVar3 == (void *)0x0) {
        local_44 = 0;
      }
      else {
        local_c4 = 0x101;
        local_c8 = 0x44870000;
        local_c0 = (char *)param_1;
        local_44 = FUN_007d1cc0("movie");
      }
      local_8 = (uint)local_8._1_3_ << 8;
      param_1[0x53] = local_44;
      local_c0 = (char *)0x79448d;
      FUN_007d3f20();
      local_c0 = "j";
      FUN_0078c480();
      local_c0 = (char *)0x7944aa;
      local_c0 = (char *)FUN_0041f870();
      local_c4 = 0x7944b9;
      FUN_007d3850();
      local_c0 = "j";
      FUN_007d3dd0();
      local_c0 = (char *)param_1[0x53];
      local_c4 = 0x7944e3;
      FUN_007d2110();
    }
  }
  else {
    FUN_007932c0();
  }
  ExceptionList = local_10;
  return param_1;
}

