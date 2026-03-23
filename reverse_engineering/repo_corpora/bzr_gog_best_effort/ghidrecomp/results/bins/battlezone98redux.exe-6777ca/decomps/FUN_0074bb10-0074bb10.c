
void FUN_0074bb10(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined4 extraout_var;
  undefined1 local_ac [4];
  undefined1 local_a8 [4];
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  uint local_80;
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bca0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_80 = 0;
  local_14 = uVar2;
  FUN_00420260(&local_78);
  uVar5 = extraout_var;
  FID_conflict_begin(local_84);
  do {
    cVar1 = FUN_00420f10(local_84);
    if (cVar1 == '\0') {
      local_a0 = FUN_0073a9f0(local_74);
      local_8 = 0;
      local_94 = local_a0;
      uVar5 = FUN_0041f870();
      FUN_007d6a70("Can\'t find user in GetPlayerNameSafe : %s\n",uVar5);
      local_8 = 0xffffffff;
      ~basic_string<>();
      basic_string<>(&DAT_008a1ad8);
      local_8 = 1;
      puVar6 = (undefined4 *)FUN_00420260(local_a8);
      local_78 = *puVar6;
      while( true ) {
        cVar1 = FUN_00420f10(local_84);
        if (cVar1 == '\0') break;
        puVar7 = local_5c;
        FUN_00422150(puVar7);
        local_a4 = FUN_0073a9f0(puVar7);
        local_8._0_1_ = 2;
        local_9c = local_a4;
        uVar5 = FUN_0041f870();
        FUN_007d6a70("   lobby : %s\n",uVar5);
        local_8 = CONCAT31(local_8._1_3_,1);
        ~basic_string<>();
        puVar7 = local_7c;
        FUN_00422150(puVar7);
        FUN_00420260(puVar7);
        puVar7 = local_8c;
        FUN_00422150(puVar7);
        FID_conflict_begin(puVar7);
        while( true ) {
          cVar1 = FUN_00420f10(local_8c);
          if (cVar1 == '\0') break;
          puVar7 = local_44;
          FUN_00422150(puVar7);
          local_98 = FUN_0073a9f0(puVar7);
          local_8._0_1_ = 3;
          local_90 = local_98;
          FUN_00422150();
          uVar5 = FUN_0041f870();
          uVar5 = FUN_0041f870(uVar5);
          FUN_007d6a70("         %s : %s\n",uVar5);
          local_8 = CONCAT31(local_8._1_3_,1);
          ~basic_string<>();
          FUN_00428570();
        }
        FUN_00428570();
      }
      basic_string<>("Not Found");
      local_80 = local_80 | 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
LAB_0074bdbf:
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    puVar7 = local_88;
    uVar3 = param_2;
    FUN_00422150(puVar7,param_2,uVar2,uVar5);
    FUN_00578c20(puVar7,uVar3);
    puVar7 = local_ac;
    FUN_00422150(puVar7);
    uVar3 = FID_conflict_begin(puVar7);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 != '\0') {
      iVar4 = FUN_00422150();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (param_1,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          *)(iVar4 + 0x30));
      local_80 = local_80 | 1;
      goto LAB_0074bdbf;
    }
    FUN_00428570();
  } while( true );
}

