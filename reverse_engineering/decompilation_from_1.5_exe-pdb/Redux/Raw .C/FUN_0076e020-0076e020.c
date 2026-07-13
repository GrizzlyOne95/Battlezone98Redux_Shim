
void FUN_0076e020(void)

{
  char cVar1;
  int iVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  uint uVar4;
  allocator<char> *paVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined1 local_124 [8];
  undefined1 local_11c [8];
  undefined1 local_114 [8];
  undefined1 local_10c [8];
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined1 local_f8 [4];
  undefined4 local_f4;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined1 local_cc [8];
  undefined1 local_c4 [6];
  char local_be;
  char local_bd;
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085dc15;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  iVar2 = FUN_0076f9f0(local_14);
  *(undefined1 *)(iVar2 + 0x90) = 1;
  pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_0076f9f0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
  local_8._0_1_ = 1;
  uVar4 = FUN_004170c0();
  iVar2 = FUN_004170c0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
            (local_2c,iVar2 - 4,uVar4);
  uVar7 = 0;
  iVar2 = FUN_0076f9f0(0);
  FUN_00666890(iVar2 + 0x18,uVar7);
  local_8._0_1_ = 2;
  cVar1 = FUN_00667410(local_5c);
  if (cVar1 == '\0') {
    local_8._0_1_ = 1;
    FUN_004180b0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_004bb3b0();
  }
  else {
    FUN_00667590();
    local_8._0_1_ = 3;
    FUN_004fbb60();
    FUN_004fbb60();
    FUN_006675b0(local_5c,local_11c);
    local_8._0_1_ = 4;
    while (cVar1 = FUN_0066e6d0(local_cc,local_10c), cVar1 != '\0') {
      puVar8 = local_114;
      puVar6 = local_124;
      FUN_0066add0(puVar6,puVar8);
      FUN_006674d0(puVar6,puVar8);
      iVar2 = get();
      if (iVar2 != 3) {
        FID_conflict_begin(local_c4);
        FID_conflict_end(local_f8);
        puVar8 = local_a4;
        paVar5 = (allocator<char> *)FUN_0066add0(puVar8);
        std::allocator<char>::allocator<char>(paVar5);
        local_f4 = FUN_008405e0(puVar8);
        local_8._0_1_ = 5;
        local_ec = local_f4;
        FUN_00417fd0(local_74);
        local_8._0_1_ = 7;
        FUN_004180b0();
        local_e8 = FUN_006ab6b0();
        local_8._0_1_ = 8;
        local_e0 = local_e8;
        FUN_00756750(local_74,local_e8);
        local_8 = CONCAT31(local_8._1_3_,7);
        FUN_00417b50();
        local_bd = '\0';
        while (cVar1 = FID_conflict_operator__(local_f8), cVar1 != '\0') {
          pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_00421ec0();
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                    (local_44,pbVar3);
          local_8._0_1_ = 9;
          local_104 = FUN_006ab6b0();
          local_8._0_1_ = 10;
          local_100 = local_104;
          FUN_00756750(local_44,local_104);
          local_8._0_1_ = 9;
          FUN_00417b50();
          local_be = FUN_0076ddf0(local_74,local_44);
          if (local_be != '\0') {
            local_bd = '\x01';
            local_8 = CONCAT31(local_8._1_3_,7);
            ~basic_string<>();
            break;
          }
          FUN_0076fa50();
          local_8 = CONCAT31(local_8._1_3_,7);
          ~basic_string<>();
        }
        if (local_bd == '\0') {
          puVar8 = local_8c;
          paVar5 = (allocator<char> *)FUN_0066add0(puVar8);
          std::allocator<char>::allocator<char>(paVar5);
          local_d8 = FUN_008405e0(puVar8);
          local_8._0_1_ = 0xb;
          local_d4 = local_d8;
          local_fc = FUN_00417fd0(local_bc);
          local_8._0_1_ = 0xc;
          local_e4 = local_fc;
          uVar7 = FUN_0041f870();
          FUN_007d6a70("    %s\n",uVar7);
          local_8._0_1_ = 0xb;
          ~basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,7);
          FUN_004180b0();
          iVar2 = FUN_0076f9f0();
          *(undefined1 *)(iVar2 + 0x90) = 0;
        }
        local_8._0_1_ = 4;
        ~basic_string<>();
      }
      FUN_0066ae00();
    }
    local_8 = CONCAT31(local_8._1_3_,3);
    FUN_00667660();
    iVar2 = FUN_0076f9f0();
    if (*(char *)(iVar2 + 0x90) == '\0') {
      FUN_0076f9f0();
      uVar7 = FUN_0041f870();
      FUN_0076f9f0(uVar7);
      uVar7 = FUN_0041f870();
      FUN_007d6a70("UNSAFE %s  :  %s\n",uVar7);
      FUN_007d6a70("---------------------------------\n");
    }
    local_8._0_1_ = 2;
    FUN_00667660();
    local_8._0_1_ = 1;
    FUN_004180b0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_004bb3b0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

