
void FUN_0073e7e0(undefined4 param_1,int param_2,char param_3)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  code *pcVar5;
  code *pcVar6;
  undefined1 local_1b8 [168];
  undefined1 local_110 [16];
  undefined4 local_100;
  undefined1 local_fc [4];
  undefined4 local_f8;
  undefined4 local_f4;
  undefined1 local_f0 [4];
  int local_ec;
  uint local_e8;
  int local_e4;
  char *local_e0;
  int local_dc;
  int *local_d8;
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ad97;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcVar6 = FUN_004bc8c0;
  pcVar5 = FUN_0056f740;
  pcVar4 = FUN_00574a10;
  FUN_0081e820("CNetGameLobby::OnPersonaStateChange called for ",param_1,&DAT_00892870);
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar6);
  if (param_3 != '\0') {
    local_e4 = FUN_0056f900();
    if (local_e4 != 0) {
      local_100 = FUN_00416410();
      FUN_0042d8c0(local_f0);
      FID_conflict_begin(local_fc);
      while (cVar1 = FUN_00420f10(local_fc), cVar1 != '\0') {
        local_dc = FUN_0042de50();
        cVar1 = FUN_0056f780(param_1);
        if (cVar1 != '\0') {
          (**(code **)(*local_d8 + 0x50))(local_2c,local_dc + 8);
          local_8 = 0;
          cVar1 = operator!=<>(local_dc + 0x2c,local_2c);
          if (cVar1 != '\0') {
            FID_conflict_operator_(local_2c);
            FUN_005788e0(local_dc + 8,local_dc + 0x2c);
          }
          basic_string<>("vehicle");
          local_8._0_1_ = 1;
          local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_5c);
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          if ((local_e0 == (char *)0x0) || (*local_e0 == '\0')) {
            FUN_0041f830();
          }
          else {
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)(local_dc + 0x48),local_e0);
          }
          basic_string<>("friendID");
          local_8._0_1_ = 2;
          local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_74);
          local_8._0_1_ = 0;
          ~basic_string<>();
          if ((local_e0 == (char *)0x0) || (*local_e0 == '\0')) {
            FUN_0056f7e0();
          }
          else {
            basic_string<>(local_e0);
            local_8._0_1_ = 3;
            FUN_006ca8e0(local_a4,1,1);
            local_8._0_1_ = 5;
            ~basic_string<>();
            FUN_0073ba90(local_1b8,local_dc + 0x18);
            local_8._0_1_ = 0;
            FUN_006b95c0();
          }
          cVar1 = FUN_00742cf0();
          if (cVar1 == '\0') {
            basic_string<>(&DAT_008757b0);
            local_8._0_1_ = 6;
            local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_d4);
            local_8 = (uint)local_8._1_3_ << 8;
            ~basic_string<>();
            local_ec = -1;
            if ((local_e0 != (char *)0x0) && (*local_e0 != '\0')) {
              local_ec = atoi(local_e0);
            }
            basic_string<>("miniid");
            local_8._0_1_ = 7;
            local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_bc);
            local_8._0_1_ = 0;
            ~basic_string<>();
            local_e8 = 0xffffffff;
            if ((local_e0 != (char *)0x0) && (*local_e0 != '\0')) {
              local_e8 = atoi(local_e0);
            }
            if ((*(int *)(local_dc + 0x80) != local_ec) ||
               (*(ushort *)(local_dc + 0x28) != local_e8)) {
              *(int *)(local_dc + 0x80) = local_ec;
              *(undefined2 *)(local_dc + 0x28) = (undefined2)local_e8;
              uVar2 = FUN_0041f870(*(undefined4 *)(local_dc + 0x80),*(undefined2 *)(local_dc + 0x28)
                                  );
              uVar2 = FUN_0081e820("Player %s set to Team %d and Player %d\n",uVar2);
              FUN_0081e710(uVar2);
            }
          }
          if (*(char *)(local_dc + 0x7c) == '\0') {
            basic_string<>("launched");
            local_8._0_1_ = 8;
            local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_8c);
            local_8._0_1_ = 0;
            ~basic_string<>();
            if ((local_e0 == (char *)0x0) || (*local_e0 != '1')) {
              local_f8 = 0;
            }
            else {
              local_f8 = 1;
            }
            *(undefined1 *)(local_dc + 0x7c) = (undefined1)local_f8;
          }
          basic_string<>("ready");
          local_8._0_1_ = 9;
          local_e0 = (char *)(**(code **)(*local_d8 + 0x28))(local_d8 + 10,param_1,local_44);
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          if (local_e0 == (char *)0x0) {
            FUN_0041f830();
          }
          else {
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)(local_dc + 100),local_e0);
          }
          cVar1 = FUN_00427310(local_dc + 100,local_e4 + 0xc0);
          if (((cVar1 == '\0') || (cVar1 = FUN_0041f890(), cVar1 != '\0')) &&
             (*(char *)(local_dc + 0x7c) == '\0')) {
            local_f4 = 0;
          }
          else {
            local_f4 = 1;
          }
          *(undefined1 *)(local_dc + 0x60) = (undefined1)local_f4;
          local_8 = 0xffffffff;
          ~basic_string<>();
          break;
        }
        FUN_0042da80();
      }
      uVar2 = (**(code **)(*local_d8 + 0x38))(local_110);
      cVar1 = FUN_0056f780(uVar2);
      if (cVar1 != '\0') {
        FUN_00742560();
      }
    }
    FUN_007476a0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

