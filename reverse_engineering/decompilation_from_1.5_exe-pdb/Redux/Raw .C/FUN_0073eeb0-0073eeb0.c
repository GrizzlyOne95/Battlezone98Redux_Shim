
void FUN_0073eeb0(undefined4 param_1,undefined4 param_2,int param_3,char param_4,char param_5,
                 char param_6)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int iVar4;
  code *pcVar5;
  undefined1 *puVar6;
  code *pcVar7;
  code *pcVar8;
  undefined1 local_100 [16];
  undefined1 local_f0 [16];
  undefined1 local_e0 [16];
  undefined1 local_d0 [16];
  undefined1 local_c0 [4];
  undefined1 local_bc [4];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined1 local_a0 [4];
  undefined4 local_9c;
  int local_98;
  char *local_94;
  int local_90;
  undefined1 local_8c [4];
  undefined4 local_88;
  undefined4 local_84;
  int local_80;
  undefined1 local_7a;
  char local_79;
  int *local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ade0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcVar8 = FUN_004bc8c0;
  pcVar7 = FUN_0056f740;
  pcVar5 = FUN_00574a10;
  FUN_0081e820("CNetGameLobby::OnLobbyChatUpdate called for lobby ",param_1,", member ",param_2,
               ", changes ");
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_0073ba70(uVar2);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_3);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar7);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
  uVar2 = (**(code **)(*local_78 + 0x38))(local_100);
  puVar6 = local_d0;
  (**(code **)(*local_78 + 0x68))(puVar6,param_1,uVar2);
  cVar1 = FUN_0056f780(puVar6);
  if (cVar1 != '\0') {
    local_98 = (**(code **)(*local_78 + 0x44))(param_1);
    basic_string<>("userCount");
    local_8 = 0;
    local_94 = (char *)(**(code **)(*local_78 + 0x2c))(param_1,local_44);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if ((local_94 == (char *)0x0) || (iVar4 = atoi(local_94), iVar4 != local_98)) {
      local_b0 = FUN_00482630(local_74,local_98);
      local_8 = 1;
      local_a4 = local_b0;
      uVar2 = FUN_0041f870();
      basic_string<>(uVar2);
      local_8._0_1_ = 2;
      basic_string<>("userCount");
      local_8._0_1_ = 3;
      (**(code **)(*local_78 + 0x20))(param_1,local_2c,local_5c);
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,1);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  cVar1 = FUN_0073ba10(param_1);
  if ((cVar1 == '\0') && (local_80 = FUN_007470b0(param_1,0), local_80 != 0)) {
    if (param_4 != '\0') {
      FUN_0042d8c0(&local_88);
      FID_conflict_begin(local_b8);
      if ((param_5 == '\0') && (param_6 == '\0')) {
        local_7a = 0;
      }
      else {
        local_7a = 1;
      }
      FUN_00578640(param_2,local_7a);
      while( true ) {
        cVar1 = FUN_00420f10(local_b8);
        if (cVar1 == '\0') goto LAB_0073f43d;
        uVar2 = param_2;
        FUN_0042da60(param_2);
        cVar1 = FUN_0056f780(uVar2);
        if (cVar1 != '\0') break;
        FUN_0042da80();
      }
      local_9c = local_88;
      FUN_00747ca0(local_c0,local_88);
      (**(code **)(*local_78 + 0x4c))(param_1,param_2);
      local_79 = '\0';
      FUN_0042d8c0(local_8c);
      FID_conflict_begin(local_a0);
      while (cVar1 = FUN_00420f10(local_a0), cVar1 != '\0') {
        iVar4 = FUN_0042da60();
        if (*(int *)(iVar4 + 0x80) < 1) {
          uVar2 = FUN_0042de50();
          FUN_007467b0(uVar2);
          local_79 = '\x01';
        }
        FUN_0042da80();
      }
      cVar1 = FUN_0056f780(local_78 + 10);
      if (cVar1 != '\0') {
        local_79 = '\x01';
      }
      local_a8 = (**(code **)(*local_78 + 0x44))(local_80 + 0x10);
      if (local_a8 == 0) {
        FUN_0042d8c0(&local_84);
        FUN_0042d8c0(local_b4);
        while (cVar1 = FUN_00420f10(local_b4), cVar1 != '\0') {
          iVar4 = local_80 + 0x10;
          FUN_0042da60(iVar4);
          cVar1 = FUN_0056f780(iVar4);
          if (cVar1 != '\0') {
            pcVar5 = FUN_004bc8c0;
            iVar4 = FUN_0042da60();
            iVar4 = FUN_0042da60(&DAT_00896ce8,iVar4 + 0x10);
            FUN_0081e820("Removing lobby : ",iVar4 + 0x68);
            uVar2 = FUN_0081e660();
            uVar2 = FUN_004bc590(uVar2);
            uVar2 = FUN_00574730(uVar2);
            uVar2 = FUN_004bc590(uVar2);
            pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
            local_ac = local_84;
            FUN_00747ca0(local_bc,local_84);
            local_79 = '\x01';
            break;
          }
          FUN_0042da80();
        }
      }
      if (local_79 != '\0') {
        uVar2 = (**(code **)(*local_78 + 0x38))(local_f0);
        cVar1 = FUN_0056f780(uVar2);
        if (cVar1 != '\0') {
          FUN_00742560();
        }
        FUN_007476a0();
      }
      FUN_00745480(0);
      goto LAB_0073f43d;
    }
    local_90 = FUN_0056f900();
    if (local_90 != 0) {
      FUN_00744a50(local_90,param_2);
      uVar2 = (**(code **)(*local_78 + 0x38))(local_e0);
      cVar1 = FUN_0056f780(uVar2);
      if (cVar1 != '\0') {
        FUN_00742560();
      }
      FUN_007476a0();
    }
  }
LAB_0073f43d:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

