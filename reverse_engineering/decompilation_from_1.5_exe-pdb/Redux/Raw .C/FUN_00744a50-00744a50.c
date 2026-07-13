
void __thiscall FUN_00744a50(int *param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined1 local_2b0 [168];
  undefined1 local_208 [16];
  undefined1 local_1f8 [4];
  undefined1 local_1f4 [4];
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  uint local_1cc;
  int local_1c8;
  char local_1c3;
  char local_1c2;
  char local_1c1;
  int *local_1c0;
  int local_1bc;
  char *local_1b8;
  undefined1 local_1b4 [24];
  undefined1 local_19c [24];
  undefined1 local_184 [24];
  undefined1 local_16c [24];
  undefined1 local_154 [24];
  undefined1 local_13c [24];
  undefined1 local_124 [24];
  undefined1 local_10c [24];
  undefined1 local_f4 [24];
  CDaoErrorInfo local_dc [8];
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined2 local_b4 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_94 [24];
  char local_7c;
  char local_60;
  int local_5c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b4f9;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c0 = param_1;
  (**(code **)(*param_1 + 0x50))(local_2c,param_3,local_14);
  local_8 = 0;
  cVar1 = FUN_0041f890();
  if (cVar1 != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"Loading User...");
  }
  local_1bc = FUN_007424e0(param_2,param_3);
  basic_string<>("launched");
  local_8._0_1_ = 1;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_f4);
  local_8._0_1_ = 0;
  ~basic_string<>();
  if ((local_1b8 == (char *)0x0) || (*local_1b8 != '1')) {
    local_1dc = 0;
  }
  else {
    local_1dc = 1;
  }
  local_1c2 = (char)local_1dc;
  basic_string<>("ready");
  local_8._0_1_ = 2;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_10c);
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  if (local_1b8 != (char *)0x0) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_44,local_1b8);
  }
  if ((((local_1b8 == (char *)0x0) || (*local_1b8 == '\0')) ||
      (cVar1 = FUN_00427310(param_2 + 0xc0,local_44), cVar1 == '\0')) && (local_1c2 == '\0')) {
    local_1d8 = 0;
  }
  else {
    local_1d8 = 1;
  }
  local_1c1 = (char)local_1d8;
  local_1c8 = -1;
  basic_string<>(&DAT_008757b0);
  local_8._0_1_ = 4;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_13c);
  local_8 = CONCAT31(local_8._1_3_,3);
  ~basic_string<>();
  if ((local_1b8 != (char *)0x0) && (*local_1b8 != '\0')) {
    local_1c8 = atoi(local_1b8);
  }
  local_1cc = 0;
  basic_string<>("miniid");
  local_8._0_1_ = 5;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_16c);
  local_8 = CONCAT31(local_8._1_3_,3);
  ~basic_string<>();
  if ((local_1b8 != (char *)0x0) && (*local_1b8 != '\0')) {
    local_1cc = atoi(local_1b8);
  }
  basic_string<>("friendID");
  local_8._0_1_ = 6;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_19c);
  local_8._0_1_ = 3;
  ~basic_string<>();
  FUN_0073a6b0();
  if ((local_1b8 != (char *)0x0) && (*local_1b8 != '\0')) {
    basic_string<>(local_1b8);
    local_8._0_1_ = 7;
    FUN_006ca8e0(local_1b4,1,1);
    local_8._0_1_ = 9;
    ~basic_string<>();
    FUN_0073ba90(local_2b0,&local_1ec);
    local_8._0_1_ = 3;
    FUN_006b95c0();
  }
  basic_string<>("vehicle");
  local_8._0_1_ = 10;
  local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_184);
  local_8._0_1_ = 3;
  ~basic_string<>();
  if (local_1bc == 0) {
    FUN_0073ce90();
    local_8 = CONCAT31(local_8._1_3_,0xb);
    FID_conflict_operator_(local_2c);
    local_d4 = *param_3;
    local_d0 = param_3[1];
    local_cc = param_3[2];
    local_c8 = param_3[3];
    if ((local_1b8 != (char *)0x0) && (*local_1b8 != '\0')) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_94,local_1b8);
    }
    local_7c = local_1c1;
    FID_conflict_operator_(local_44);
    local_60 = local_1c2;
    local_c4 = local_1ec;
    local_c0 = local_1e8;
    local_bc = local_1e4;
    local_b8 = local_1e0;
    cVar1 = FUN_00742d50(param_2 + 0x10);
    if ((cVar1 == '\0') || (*(char *)(param_2 + 0xb0) != '\0')) {
      local_5c = local_1c8;
      local_b4[0] = (undefined2)local_1cc;
      if (local_1cc != 0) {
        puVar6 = local_b4;
        puVar2 = &local_d4;
        FUN_007659f0(puVar2,puVar6);
        FUN_0073bb60(puVar2,puVar6);
      }
      uVar4 = FUN_0041f870(local_5c,local_b4[0]);
      uVar4 = FUN_0081e820("Player %s set to Team %d and Player %d\n",uVar4);
      FUN_0081e710(uVar4);
    }
    else {
      local_1c8 = 0;
      local_1c3 = '\x01';
      while (local_1c3 != '\0') {
        local_1c8 = local_1c8 + 1;
        local_1c3 = '\0';
        puVar2 = (undefined4 *)FUN_0042d8c0(local_1f8);
        local_1d0 = *puVar2;
        puVar2 = (undefined4 *)FID_conflict_begin(local_1f4);
        local_1f0 = *puVar2;
        cVar1 = FUN_00420f10(&local_1f0);
        if (cVar1 != '\0') {
          iVar3 = FUN_004305e0();
          if (*(int *)(iVar3 + 0x80) != local_1c8) {
                    /* WARNING: Subroutine does not return */
            FUN_0042de70();
          }
          local_1c3 = '\x01';
        }
      }
      FUN_007468b0(local_dc,local_1c8);
    }
    FUN_00747c70(local_dc);
    local_1bc = FUN_0045e220();
    FUN_00745480(0);
    local_8._0_1_ = 3;
    CDaoErrorInfo::~CDaoErrorInfo(local_dc);
  }
  else {
    if ((local_1c1 == '\0') && (*(char *)(local_1bc + 0x7c) == '\0')) {
      local_1d4 = 0;
    }
    else {
      local_1d4 = 1;
    }
    local_1c1 = (char)local_1d4;
    cVar1 = operator!=<>(local_1bc + 0x2c,local_2c);
    if (cVar1 != '\0') {
      FUN_005788e0(local_1bc + 8,local_1bc + 0x2c);
      FID_conflict_operator_(local_2c);
    }
    if ((local_1b8 == (char *)0x0) || (*local_1b8 == '\0')) {
      FUN_0041f830();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (local_1bc + 0x48),local_1b8);
    }
    *(char *)(local_1bc + 0x60) = local_1c1;
    FID_conflict_operator_(local_44);
    *(undefined4 *)(local_1bc + 0x18) = local_1ec;
    *(undefined4 *)(local_1bc + 0x1c) = local_1e8;
    *(undefined4 *)(local_1bc + 0x20) = local_1e4;
    *(undefined4 *)(local_1bc + 0x24) = local_1e0;
    if (*(char *)(param_2 + 0xb0) == '\0') {
      uVar4 = (**(code **)(*local_1c0 + 0x38))(local_208);
      cVar1 = FUN_0073ba10(uVar4);
      if (cVar1 != '\0') {
        basic_string<>("clientsconnected");
        local_8._0_1_ = 0xc;
        local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_124);
        local_8 = CONCAT31(local_8._1_3_,3);
        ~basic_string<>();
        if ((local_1b8 == (char *)0x0) || (*local_1b8 == '\0')) {
          *(undefined4 *)(local_1bc + 0x84) = 0;
        }
        else {
          iVar3 = atoi(local_1b8);
          *(int *)(local_1bc + 0x84) = iVar3;
        }
        basic_string<>("clientsremotedup");
        local_8._0_1_ = 0xd;
        local_1b8 = (char *)(**(code **)(*local_1c0 + 0x28))(param_2 + 0x10,param_3,local_154);
        local_8._0_1_ = 3;
        ~basic_string<>();
        if ((local_1b8 == (char *)0x0) || (*local_1b8 == '\0')) {
          *(undefined4 *)(local_1bc + 0x88) = 0;
        }
        else {
          iVar3 = atoi(local_1b8);
          *(int *)(local_1bc + 0x88) = iVar3;
        }
      }
      cVar1 = FUN_00742d50(param_2 + 0x10);
      if ((cVar1 == '\0') &&
         ((*(int *)(local_1bc + 0x80) != local_1c8 || (*(ushort *)(local_1bc + 0x28) != local_1cc)))
         ) {
        *(int *)(local_1bc + 0x80) = local_1c8;
        *(undefined2 *)(local_1bc + 0x28) = (undefined2)local_1cc;
        FUN_00745480(0);
        iVar3 = local_1bc + 0x28;
        iVar5 = local_1bc + 8;
        FUN_007659f0(iVar5,iVar3);
        FUN_0073bb60(iVar5,iVar3);
        uVar4 = FUN_0041f870(*(undefined4 *)(local_1bc + 0x80),*(undefined2 *)(local_1bc + 0x28));
        uVar4 = FUN_0081e820("Player %s set to Team %d and Player %d\n",uVar4);
        FUN_0081e710(uVar4);
      }
      if ((local_1c2 != '\0') && (*(char *)(local_1bc + 0x7c) == '\0')) {
        *(undefined1 *)(local_1bc + 0x7c) = 1;
      }
    }
  }
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

