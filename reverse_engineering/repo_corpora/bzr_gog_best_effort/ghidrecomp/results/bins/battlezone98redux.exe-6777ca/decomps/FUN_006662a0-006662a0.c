
void FUN_006662a0(undefined4 param_1,int *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined1 *puVar6;
  undefined1 local_e8 [4];
  undefined1 local_e4 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_e0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_dc;
  undefined4 local_d8;
  undefined1 local_d4 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_d0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_cc;
  uint local_c8;
  undefined4 local_c4;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  undefined1 local_b4 [4];
  undefined4 local_b0;
  uint local_ac;
  int local_a8;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e20b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_ac = 0;
  local_14 = uVar2;
  basic_string<>("1024 x 768");
  local_8 = 0;
  local_c8 = 0;
  local_b8 = 0;
  if (param_2 == (int *)0x0) {
    basic_string<>(local_44);
    local_ac = local_ac | 1;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    local_c4 = (**(code **)(*param_2 + 0xc))(uVar2);
    FUN_00422170();
    basic_string<>("Video Mode");
    local_8._0_1_ = 1;
    puVar3 = (undefined4 *)FUN_00421e00(local_e8,local_5c);
    local_b0 = *puVar3;
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    uVar4 = FID_conflict_begin(local_e4);
    cVar1 = FUN_004221b0(uVar4);
    if (cVar1 == '\0') {
      puVar6 = local_b4;
      FUN_00421ea0(puVar6);
      FUN_0041fc00(puVar6);
      puVar6 = local_d4;
      FUN_00421ea0(puVar6);
      FUN_0041fc60(puVar6);
      while( true ) {
        cVar1 = FID_conflict_operator__(local_d4);
        if (cVar1 == '\0') break;
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 get();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_2c,pbVar5);
        local_8 = CONCAT31(local_8._1_3_,2);
        local_a8 = FUN_005871b0(&DAT_008921ec,0);
        if (local_a8 != -1) {
          local_d8 = FUN_0045e1d0(local_8c,0,local_a8);
          FUN_0045e0f0(local_d8);
          ~basic_string<>();
        }
        local_a8 = FUN_00666640(0x78,0);
        if (local_a8 != -1) {
          local_d0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )FUN_0045e1d0(local_74,0,local_a8);
          local_8._0_1_ = 3;
          local_cc = local_d0;
          local_c0 = Ogre::StringConverter::parseUnsignedInt(local_d0,0);
          local_8._0_1_ = 2;
          ~basic_string<>();
          local_e0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )FUN_0045e1d0(local_a4,local_a8 + 1,0xffffffff);
          local_8._0_1_ = 4;
          local_dc = local_e0;
          local_bc = Ogre::StringConverter::parseUnsignedInt(local_e0,0);
          local_8 = CONCAT31(local_8._1_3_,2);
          ~basic_string<>();
          if ((local_b8 < local_bc) || ((local_bc == local_b8 && (local_c8 < local_c0)))) {
            local_b8 = local_bc;
            local_c8 = local_c0;
            uVar4 = get();
            FID_conflict_operator_(uVar4);
          }
        }
        FUN_00666870();
        local_8 = local_8 & 0xffffff00;
        ~basic_string<>();
      }
      basic_string<>(local_44);
      local_ac = local_ac | 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      basic_string<>(local_44);
      local_ac = local_ac | 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

