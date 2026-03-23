
void FUN_006f8390(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uStack_16c;
  undefined1 *puStack_168;
  undefined1 *puStack_160;
  char *pcStack_15c;
  code *pcStack_158;
  uint uStack_154;
  undefined1 local_150 [24];
  undefined1 local_138 [24];
  undefined1 local_120 [8];
  undefined1 local_118 [8];
  undefined4 local_110;
  undefined1 *local_10c;
  undefined1 *local_108;
  undefined1 local_104 [8];
  undefined1 *local_fc;
  undefined1 local_f8 [8];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  char *local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  code *local_c8;
  undefined1 *local_c4;
  char *local_c0;
  code *local_bc;
  undefined1 *local_b8;
  undefined4 *local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  int *local_98;
  char local_91;
  int local_90;
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085588c;
  local_10 = ExceptionList;
  uStack_154 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_158 = (code *)0x899314;
  pcStack_15c = (char *)0x400;
  puStack_160 = (undefined1 *)0x6f83dc;
  local_14 = uStack_154;
  FUN_006d08b0();
  pcStack_158 = (code *)0x6f83ed;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    pcStack_158 = (code *)0x899358;
    pcStack_15c = (char *)0x20;
    puStack_160 = (undefined1 *)0x6f84d7;
    FUN_006d47b0();
  }
  else {
    pcStack_158 = (code *)0x6f8403;
    FUN_006ab750();
    pcStack_158 = (code *)0x6f8414;
    local_98 = (int *)FUN_00421ec0();
    pcStack_158 = (code *)(local_90 + 0x4bd4);
    local_fc = (undefined1 *)&puStack_160;
    puStack_168 = (undefined1 *)0x6f8443;
    local_ec = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_160,
                          (shared_ptr<class___ExceptionPtr> *)(local_90 + 0x4bb4));
    puStack_168 = local_120;
    uStack_16c = 0x6f8470;
    local_b4 = (undefined4 *)(**(code **)(*local_98 + 0x1c))();
    local_a0 = *local_b4;
    local_9c = local_b4[1];
    pcStack_158 = (code *)0x6f8498;
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      pcStack_158 = (code *)0x899588;
      pcStack_15c = (char *)0x6f84e9;
      basic_string<>();
      local_8 = 0;
      pcStack_158 = (code *)local_5c;
      pcStack_15c = (char *)0x6f8505;
      FUN_006b7490();
      pcStack_158 = (code *)0x6f850c;
      local_91 = FUN_0041f890();
      local_8 = 0xffffffff;
      pcStack_158 = (code *)0x6f8521;
      ~basic_string<>();
      if (local_91 != '\0') {
        pcStack_158 = (code *)0x6f8541;
        cVar1 = FUN_0041f890();
        if (cVar1 == '\0') {
          pcStack_158 = (code *)0x899588;
          pcStack_15c = (char *)0x6f8555;
          basic_string<>();
          local_8 = 1;
          pcStack_158 = (code *)(local_90 + 0x900);
          pcStack_15c = local_44;
          puStack_160 = (undefined1 *)0x6f857e;
          FUN_006b7810();
          local_8 = 0xffffffff;
          pcStack_158 = (code *)0x6f858d;
          ~basic_string<>();
        }
        else {
          pcStack_158 = (code *)0x899588;
          pcStack_15c = (char *)0x6f859c;
          basic_string<>();
          local_8 = 2;
          pcStack_158 = (code *)local_2c;
          pcStack_15c = (char *)0x6f85b8;
          FUN_006b7840();
          local_8 = 0xffffffff;
          pcStack_158 = (code *)0x6f85c7;
          ~basic_string<>();
        }
      }
      pcStack_158 = (code *)local_8c;
      pcStack_15c = (char *)0x6f85df;
      pcStack_158 = (code *)FUN_006b87d0();
      pcStack_15c = (char *)0x6f85fd;
      local_a8 = pcStack_158;
      FUN_0045e0f0();
      pcStack_158 = (code *)0x6f8608;
      ~basic_string<>();
      pcStack_158 = (code *)0x400;
      pcStack_15c = (char *)0x6f861e;
      cVar1 = FUN_006d4590();
      if (cVar1 != '\0') {
        pcStack_158 = (code *)(local_90 + 0x4a68);
        pcStack_15c = "Raw Handshake request:\n";
        puStack_160 = local_74;
        pcStack_158 = (code *)FUN_0066e860();
        local_8 = 3;
        pcStack_15c = (char *)0x400;
        puStack_160 = (undefined1 *)0x6f8679;
        local_d0 = pcStack_158;
        local_b0 = pcStack_158;
        FUN_006d4480();
        local_8 = 0xffffffff;
        pcStack_158 = (code *)0x6f8688;
        ~basic_string<>();
      }
      if (0 < *(int *)(local_90 + 0xa10)) {
        local_bc = FUN_007098c0;
        local_b8 = (undefined1 *)0x0;
        pcStack_158 = (code *)local_118;
        pcStack_15c = (char *)0x6f86c1;
        pcStack_15c = (char *)FUN_006e1540();
        local_8 = 4;
        pcStack_158 = _1_exref;
        puStack_160 = local_b8;
        puStack_168 = local_138;
        uStack_16c = 0x6f8702;
        local_e0 = pcStack_15c;
        local_d8 = pcStack_15c;
        local_e8 = FUN_006eadb0();
        local_8._0_1_ = 5;
        local_108 = (undefined1 *)&uStack_16c;
        local_ac = local_e8;
        local_110 = FUN_006eae00(local_e8);
        pcStack_158 = (code *)FUN_006d4050(local_f8,*(undefined4 *)(local_90 + 0xa10));
        pcStack_15c = (char *)0x6f8781;
        local_dc = pcStack_158;
        local_a4 = pcStack_158;
        FID_conflict_operator_();
        pcStack_158 = (code *)0x6f878c;
        FUN_006ca8c0();
        local_8 = CONCAT31(local_8._1_3_,4);
        pcStack_158 = (code *)0x6f879b;
        ~input_processor<>();
        local_8 = 0xffffffff;
        pcStack_158 = (code *)0x6f87ad;
        FUN_006ca8c0();
      }
      local_c8 = FUN_00709670;
      local_c4 = (undefined1 *)0x0;
      pcStack_158 = (code *)local_104;
      pcStack_15c = (char *)0x6f87d3;
      pcStack_15c = (char *)FUN_006e1540();
      local_8 = 6;
      pcStack_158 = _1_exref;
      puStack_160 = local_c4;
      puStack_168 = local_150;
      uStack_16c = 0x6f8814;
      local_d4 = pcStack_15c;
      local_c0 = pcStack_15c;
      local_e4 = FUN_006eadb0();
      local_8._0_1_ = 7;
      local_10c = (undefined1 *)&uStack_16c;
      local_cc = local_e4;
      local_f0 = FUN_006eae00(local_e4);
      uVar2 = FUN_004170c0();
      uVar3 = FUN_00430770(uVar2);
      FUN_006fff30(uVar3,uVar2);
      local_8 = CONCAT31(local_8._1_3_,6);
      pcStack_158 = (code *)0x6f8888;
      ~input_processor<>();
      local_8 = 0xffffffff;
      pcStack_158 = (code *)0x6f889a;
      FUN_006ca8c0();
    }
    else {
      pcStack_158 = (code *)&local_a0;
      pcStack_15c = "Internal library error: Processor";
      puStack_160 = (undefined1 *)0x20;
      FUN_006f90a0();
    }
  }
  ExceptionList = local_10;
  uStack_154 = 0x6f88af;
  FUN_0083e885();
  return;
}

