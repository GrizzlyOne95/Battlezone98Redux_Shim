
/* WARNING: Removing unreachable block (ram,0x0073f4ff) */

void FUN_0073f460(undefined1 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  uint uVar4;
  char *_Format;
  int iVar5;
  code *pcStack_b54;
  undefined1 *puStack_b50;
  undefined1 *puVar6;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *p_Var7;
  code *pcVar8;
  basic_istream<char,struct_std::char_traits<char>_> local_b38 [184];
  basic_ostream<char,struct_std::char_traits<char>_> local_a80 [160];
  basic_istream<char,struct_std::char_traits<char>_> local_9e0 [264];
  undefined1 local_8d8 [64];
  basic_ostream<char,struct_std::char_traits<char>_> local_898 [208];
  undefined4 local_7c8;
  undefined1 *local_7c4;
  undefined4 local_7c0;
  int local_7b0;
  undefined4 local_7ac;
  undefined4 local_7a8;
  undefined4 local_7a4;
  undefined4 local_7a0;
  undefined4 local_79c;
  undefined4 local_794;
  undefined4 local_790;
  undefined4 local_78c;
  undefined4 local_788;
  undefined4 local_784;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *local_780;
  undefined4 local_77c;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *local_778;
  undefined4 local_774;
  undefined4 local_770;
  undefined4 local_76c;
  undefined4 local_768;
  undefined4 local_764;
  undefined4 local_760;
  undefined4 local_75c;
  undefined4 local_758;
  undefined4 local_754;
  undefined4 local_750;
  undefined4 local_74c;
  undefined4 local_748;
  undefined4 local_744;
  undefined4 local_740;
  undefined4 local_73c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_728;
  int local_724;
  undefined4 local_720;
  basic_ostream<char,struct_std::char_traits<char>_> *local_71c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_718;
  basic_ostream<char,struct_std::char_traits<char>_> *local_714;
  int local_710;
  basic_ostream<char,struct_std::char_traits<char>_> *local_70c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_708;
  basic_ostream<char,struct_std::char_traits<char>_> *local_704;
  basic_ostream<char,struct_std::char_traits<char>_> *local_700;
  int local_6fc;
  int local_6f8 [3];
  int local_6ec;
  int local_6e8;
  int local_6e4;
  int local_6e0;
  char local_6dc;
  char local_6db;
  char local_6da;
  char local_6d9;
  int *local_6d8;
  undefined1 local_6a4 [288];
  undefined1 local_584 [96];
  undefined1 local_524 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_4f4 [96];
  undefined1 local_494 [1023];
  undefined1 uStack_95;
  char local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085af95;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0073ba10();
  if (cVar1 != '\0') goto LAB_0074089b;
  p_Var7 = (_func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
            *)0x400;
  puStack_b50 = param_1;
  pcStack_b54 = (code *)0x73f4da;
  local_7c0 = (**(code **)(*local_6d8 + 0x78))();
  local_720 = 0x3ff;
  uStack_95 = 0;
  pcStack_b54 = FUN_004bc8c0;
  FUN_0081e820("Receiving from ",param_2,&DAT_00874924,local_494);
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,p_Var7);
  if ((DAT_02cc38a8 & 1) == 0) {
    DAT_02cc38a8 = DAT_02cc38a8 | 1;
    local_8 = 0;
    local_784 = basic_string<>();
    local_8._0_1_ = 1;
    local_75c = local_784;
    local_79c = FUN_0045f170();
    local_8._0_1_ = 2;
    local_758 = local_79c;
    FUN_0045f170();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_0083e979();
    local_8 = 0xffffffff;
  }
  if ((DAT_02cc38a8 & 2) == 0) {
    DAT_02cc38a8 = DAT_02cc38a8 | 2;
    local_8 = 3;
    local_78c = basic_string<>();
    local_8._0_1_ = 4;
    local_764 = local_78c;
    local_740 = FUN_0045f170();
    local_8._0_1_ = 5;
    local_73c = local_740;
    FUN_0045f170();
    local_8._0_1_ = 4;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    FUN_0083e979();
    local_8 = 0xffffffff;
  }
  if ((DAT_02cc38a8 & 4) == 0) {
    DAT_02cc38a8 = DAT_02cc38a8 | 4;
    local_8 = 6;
    local_774 = basic_string<>();
    local_8._0_1_ = 7;
    local_748 = local_774;
    local_794 = FUN_0045f170();
    local_8._0_1_ = 8;
    local_77c = local_794;
    FUN_0045f170();
    local_8._0_1_ = 7;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,6);
    ~basic_string<>();
    FUN_0083e979();
    local_8 = 0xffffffff;
  }
  if ((DAT_02cc38a8 & 8) == 0) {
    DAT_02cc38a8 = DAT_02cc38a8 | 8;
    local_8 = 9;
    local_7a4 = basic_string<>();
    local_8._0_1_ = 10;
    local_74c = local_7a4;
    local_760 = FUN_0045f170();
    local_8._0_1_ = 0xb;
    local_754 = local_760;
    FUN_0045f170();
    local_8._0_1_ = 10;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,9);
    ~basic_string<>();
    FUN_0083e979();
    local_8 = 0xffffffff;
  }
  basic_string<>();
  local_8 = 0xc;
  FUN_0045e1d0();
  local_8._0_1_ = 0xd;
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    if ((DAT_02cc38a8 & 0x10) == 0) {
      DAT_02cc38a8 = DAT_02cc38a8 | 0x10;
      local_8._0_1_ = 0xe;
      basic_string<>();
      FUN_0083e979();
      local_8._0_1_ = 0xd;
    }
    FUN_0073bca0();
    cVar1 = FUN_0073ba10();
    if (cVar1 == '\0') {
      local_6fc = FUN_007470b0();
      if (local_6fc == 0) {
        local_8 = CONCAT31(local_8._1_3_,0xc);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        cVar1 = FUN_00427310();
        if ((cVar1 == '\0') || (*(char *)(local_6fc + 0xb0) == '\0')) {
          FUN_0073d480();
          local_8._0_1_ = 0xf;
          (**(code **)(*local_6d8 + 0x38))();
          FUN_0073a9f0();
          local_8._0_1_ = 0x10;
          uVar4 = FUN_0048a830();
          if (2 < uVar4) {
            FUN_006cf480();
            cVar1 = FUN_00427310();
            if (cVar1 == '\0') {
              FUN_006cf480();
              FUN_0073a7a0();
              local_710 = FUN_00746690();
              if (local_710 != 0) {
                FUN_0041f870();
                _Format = (char *)FUN_0081cb40();
                sprintf(local_94,_Format);
                basic_string<>();
                local_8._0_1_ = 0x11;
                FUN_00745770();
                local_8._0_1_ = 0x10;
                ~basic_string<>();
              }
            }
            else {
              *(undefined1 *)(local_6d8 + 0x28) = 1;
            }
          }
          local_8._0_1_ = 0xf;
          ~basic_string<>();
          local_8._0_1_ = 0xd;
          FUN_0048a040();
          local_8 = CONCAT31(local_8._1_3_,0xc);
          ~basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        else {
          local_8 = CONCAT31(local_8._1_3_,0xc);
          ~basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
      }
    }
    else {
      local_8 = CONCAT31(local_8._1_3_,0xc);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    goto LAB_0074089b;
  }
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    local_770 = FUN_0045e1d0();
    local_8._0_1_ = 0x12;
    local_768 = local_770;
    FUN_006ca8e0();
    local_8._0_1_ = 0x14;
    ~basic_string<>();
    FUN_0073a6b0();
    FUN_0073ba90();
    local_6d9 = ' ';
    std::basic_istream<char,struct_std::char_traits<char>_>::get(local_9e0,&local_6d9);
    if (local_6d9 == '~') {
      local_6ec = -1;
      std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_9e0,&local_6ec);
      local_6d9 = ' ';
      std::basic_istream<char,struct_std::char_traits<char>_>::get(local_9e0,&local_6d9);
      if (local_6d9 == '~') {
        local_6f8[0] = -1;
        std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_9e0,local_6f8);
        (**(code **)(*local_6d8 + 0x38))();
        cVar1 = FUN_0056f780();
        if (cVar1 != '\0') {
          FUN_00574400();
          local_8._0_1_ = 0x15;
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_a80,local_6ec);
          basic_string<>();
          local_8._0_1_ = 0x16;
          p_Var7 = (_func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
                    *)GetPolicy();
          local_8._0_1_ = 0x17;
          puVar6 = local_584;
          local_780 = p_Var7;
          local_778 = p_Var7;
          FUN_0073bcf0();
          (**(code **)(*local_6d8 + 0x1c))();
          local_8._0_1_ = 0x16;
          ~basic_string<>();
          local_8._0_1_ = 0x15;
          ~basic_string<>();
          puStack_b50 = (undefined1 *)0x73fe13;
          basic_string<>();
          local_8._0_1_ = 0x18;
          puStack_b50 = (undefined1 *)0x73fe29;
          FUN_0071b8f0();
          local_8._0_1_ = 0x15;
          ~basic_string<>();
          puStack_b50 = (undefined1 *)0x73fe4b;
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                    (local_a80,local_6f8[0]);
          puStack_b50 = (undefined1 *)0x73fe5b;
          basic_string<>();
          local_8._0_1_ = 0x19;
          puStack_b50 = (undefined1 *)0x73fe71;
          local_790 = GetPolicy();
          local_8._0_1_ = 0x1a;
          puStack_b50 = local_524;
          pcStack_b54 = (code *)local_8d8;
          local_788 = local_790;
          pcStack_b54 = (code *)FUN_0073bcf0();
          (**(code **)(*local_6d8 + 0x1c))();
          local_8._0_1_ = 0x19;
          ~basic_string<>();
          local_8._0_1_ = 0x15;
          ~basic_string<>();
          iVar5 = local_6ec;
          FUN_0081e820("Assigned Team ",local_6ec,", player ",local_6f8[0],FUN_004bc8c0);
          uVar2 = FUN_0081e660();
          pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
          pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar5)
          ;
          pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar3);
          pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar3,(int)puVar6);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,p_Var7);
          local_8._0_1_ = 0x14;
          FUN_00417f10();
        }
        local_8._0_1_ = 0xd;
        FUN_006b95c0();
        local_8 = CONCAT31(local_8._1_3_,0xc);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        local_8._0_1_ = 0xd;
        FUN_006b95c0();
        local_8 = CONCAT31(local_8._1_3_,0xc);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    else {
      local_8._0_1_ = 0xd;
      FUN_006b95c0();
      local_8 = CONCAT31(local_8._1_3_,0xc);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    goto LAB_0074089b;
  }
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    local_6e0 = FUN_0056f900();
    if (local_6e0 != 0) {
      FUN_00743f40();
      FUN_0042d8c0();
      FID_conflict_begin();
      while (cVar1 = FUN_00420f10(), cVar1 != '\0') {
        FUN_0042da60();
        FUN_00744a50();
        FUN_0042da80();
      }
      local_7a8 = FUN_0045e1d0();
      local_8._0_1_ = 0x1b;
      local_7a0 = local_7a8;
      FUN_006ca8e0();
      local_8 = CONCAT31(local_8._1_3_,0x1d);
      ~basic_string<>();
      FUN_0073a6b0();
      FUN_0073ba90();
      local_6dc = ' ';
      std::basic_istream<char,struct_std::char_traits<char>_>::get(local_b38,&local_6dc);
      (**(code **)(*local_6d8 + 0x38))();
      cVar1 = FUN_0056f780();
      if (cVar1 != '\0') {
        FUN_00745480();
        pcVar8 = FUN_004bc8c0;
        FUN_0081e820();
        FUN_0081e660();
        puStack_b50 = (undefined1 *)0x74012b;
        FUN_004bc590();
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
      }
      local_8._0_1_ = 0xd;
      FUN_006b95c0();
    }
    local_8 = CONCAT31(local_8._1_3_,0xc);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    goto LAB_0074089b;
  }
  local_6da = '\0';
  local_6db = '\0';
  (**(code **)(*local_6d8 + 0x38))();
  cVar1 = FUN_0056f780();
  if (cVar1 != '\0') {
    local_8 = CONCAT31(local_8._1_3_,0xc);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    goto LAB_0074089b;
  }
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    local_6db = '\x01';
    FUN_0073d480();
    local_8._0_1_ = 0x1e;
    (**(code **)(*local_6d8 + 0x38))();
    FUN_0073a9f0();
    local_8._0_1_ = 0x1f;
    uVar4 = FUN_0048a830();
    if (uVar4 < 5) {
      local_8._0_1_ = 0x1e;
      ~basic_string<>();
      local_8._0_1_ = 0xd;
      FUN_0048a040();
      local_8 = CONCAT31(local_8._1_3_,0xc);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      goto LAB_0074089b;
    }
    FUN_006cf480();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
      FUN_006cf480();
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') goto LAB_007402ef;
    }
    else {
LAB_007402ef:
      local_6da = '\x01';
      FUN_006cf480();
      FID_conflict_operator_();
    }
    local_8._0_1_ = 0x1e;
    ~basic_string<>();
    local_8._0_1_ = 0xd;
    FUN_0048a040();
  }
  if ((local_6db == '\0') || (local_6da != '\0')) {
    FUN_00574400();
    local_8 = CONCAT31(local_8._1_3_,0x20);
    if (local_6da != '\0') {
      if (&stack0x00000000 == (undefined1 *)0x8a8) {
        local_718 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_718 = local_898;
      }
      FUN_004bc590();
      if (&stack0x00000000 == (undefined1 *)0x8a8) {
        local_700 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_700 = local_898;
      }
      FUN_0081cb40();
      FUN_004bc590();
      if (&stack0x00000000 == (undefined1 *)0x8a8) {
        local_728 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_728 = local_898;
      }
      FUN_004bc590();
    }
    local_7b0 = (**(code **)(*local_6d8 + 0x44))();
    for (local_6e4 = 0; local_6e4 < local_7b0; local_6e4 = local_6e4 + 1) {
      (**(code **)(*local_6d8 + 0x48))();
      cVar1 = FUN_0056f780();
      if (cVar1 != '\0') {
        local_6e8 = FUN_0056f900();
        if (local_6e8 == 0) {
          local_8._0_1_ = 0xd;
          FUN_00417f10();
          local_8 = CONCAT31(local_8._1_3_,0xc);
          ~basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
          goto LAB_0074089b;
        }
        FUN_0042d8c0();
        FID_conflict_begin();
        goto LAB_00740536;
      }
    }
    goto LAB_007406c7;
  }
  goto LAB_0074087a;
LAB_00740536:
  cVar1 = FUN_00420f10();
  if (cVar1 == '\0') goto LAB_007405cc;
  local_724 = FUN_0042de50();
  cVar1 = FUN_0056f780();
  if ((cVar1 != '\0') && (*(char *)(local_724 + 0x44) != '\0')) {
    local_8._0_1_ = 0xd;
    FUN_00417f10();
    local_8 = CONCAT31(local_8._1_3_,0xc);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
    goto LAB_0074089b;
  }
  FUN_0042da80();
  goto LAB_00740536;
LAB_007405cc:
  (**(code **)(*local_6d8 + 0x50))();
  local_8 = CONCAT31(local_8._1_3_,0x21);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    if (&stack0x00000000 == (undefined1 *)0x8a8) {
      local_70c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_70c = local_898;
    }
    puStack_b50 = (undefined1 *)0x74063b;
    FUN_00574730();
  }
  else {
    if (&stack0x00000000 == (undefined1 *)0x8a8) {
      local_71c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_71c = local_898;
    }
    puStack_b50 = (undefined1 *)0x740675;
    FUN_0073ba70();
  }
  if (&stack0x00000000 == (undefined1 *)0x8a8) {
    local_714 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_714 = local_898;
  }
  puStack_b50 = (undefined1 *)0x7406ae;
  FUN_004bc590();
  local_8 = CONCAT31(local_8._1_3_,0x20);
  ~basic_string<>();
LAB_007406c7:
  if (&stack0x00000000 == (undefined1 *)0x8a8) {
    local_704 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_704 = local_898;
  }
  FUN_004bc590();
  if (&stack0x00000000 == (undefined1 *)0x8a8) {
    local_708 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_708 = local_898;
  }
  FUN_00574730();
  GetPolicy();
  local_8._0_1_ = 0x22;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_898,FUN_004bc8c0);
  local_76c = GetPolicy();
  local_8._0_1_ = 0x23;
  local_750 = local_76c;
  FUN_0081e8a0();
  FUN_0081e6c0();
  local_8 = CONCAT31(local_8._1_3_,0x22);
  ~basic_string<>();
  if ((char)local_6d8[0x30] == '\x01') {
    local_7c4 = (undefined1 *)&pcStack_b54;
    local_7c8 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)&pcStack_b54,local_4f4);
    local_7ac = FUN_0073bdb0(local_6a4);
    local_744 = local_7ac;
    FUN_0045e0f0();
    ~basic_string<>();
  }
  FUN_00747e10();
  uVar4 = FUN_004170c0();
  if (1000 < uVar4) {
    FUN_00747f30();
  }
  FUN_007476a0();
  local_8._0_1_ = 0x20;
  ~basic_string<>();
  local_8._0_1_ = 0xd;
  FUN_00417f10();
LAB_0074087a:
  local_8 = CONCAT31(local_8._1_3_,0xc);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_0074089b:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

