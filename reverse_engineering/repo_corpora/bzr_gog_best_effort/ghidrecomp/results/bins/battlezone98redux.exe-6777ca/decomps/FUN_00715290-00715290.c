
void FUN_00715290(error_condition *param_1)

{
  bool bVar1;
  char cVar2;
  error_condition *peVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uStack_198;
  undefined1 *puStack_194;
  code *pcStack_190;
  undefined1 *puStack_18c;
  char *pcStack_188;
  undefined1 local_17c [24];
  undefined1 local_164 [8];
  undefined1 local_15c [16];
  undefined4 local_14c;
  undefined1 *local_148;
  undefined4 local_144;
  code *local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  int *local_114;
  uint local_110;
  char local_10a;
  char local_109;
  int local_108;
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [120];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858052;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_188 = (char *)0x400;
  puStack_18c = (undefined1 *)0x7152dc;
  FUN_006d08b0();
  pcStack_188 = local_15c;
  puStack_18c = (undefined1 *)0x7152ea;
  peVar3 = (error_condition *)make_error_code();
  pcStack_188 = (char *)0x7152f6;
  bVar1 = std::error_condition::operator==(param_1,peVar3);
  if (bVar1) {
    pcStack_188 = (char *)0x1000;
    puStack_18c = (undefined1 *)0x715318;
    FUN_006d08b0();
  }
  else {
    iVar4 = FUN_006b8f30();
    if (iVar4 == 0) {
      pcStack_188 = (char *)0x715348;
      FUN_006b9910();
      pcStack_188 = local_164;
      puStack_18c = (undefined1 *)0x715356;
      puVar5 = (undefined4 *)make_error_code();
      uVar6 = puVar5[1];
      *(undefined4 *)(local_108 + 0x4c28) = *puVar5;
      *(undefined4 *)(local_108 + 0x4c2c) = uVar6;
    }
    else {
      uVar6 = *(undefined4 *)(param_1 + 4);
      *(undefined4 *)(local_108 + 0x4c28) = *(undefined4 *)param_1;
      *(undefined4 *)(local_108 + 0x4c2c) = uVar6;
    }
    pcStack_188 = (char *)0x715399;
    basic_string<>();
    local_8 = 0;
    pcStack_188 = (char *)0x7153b5;
    FUN_006b7470();
    local_8 = 0xffffffff;
    ~basic_string<>();
    pcStack_188 = (char *)0x7153d4;
    basic_string<>();
    local_8 = 1;
    pcStack_188 = (undefined1 *)0x7153f3;
    FUN_006b7490();
    local_10a = FUN_0041f890();
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (local_10a != '\0') {
      cVar2 = FUN_0041f890();
      if (cVar2 == '\0') {
        pcStack_188 = (char *)0x715446;
        basic_string<>();
        local_8 = 2;
        pcStack_188 = local_44;
        puStack_18c = (undefined1 *)0x71546f;
        FUN_006b7810();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        pcStack_188 = (char *)0x71548d;
        basic_string<>();
        local_8 = 3;
        pcStack_188 = (undefined1 *)0x7154a9;
        FUN_006b7840();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    cVar2 = FUN_006ab7d0();
    if (cVar2 == '\0') {
      pcStack_188 = (char *)0x715551;
      local_144 = FUN_006b9760();
      pcStack_188 = (char *)0x71556f;
      FUN_0045e0f0();
      ~basic_string<>();
    }
    else {
      local_114 = (int *)FUN_00421ec0();
      pcStack_188 = local_d4;
      puStack_18c = (undefined1 *)0x71550e;
      local_128 = (**(code **)(*local_114 + 0x24))();
      pcStack_188 = (char *)0x71552c;
      FUN_0045e0f0();
      ~basic_string<>();
    }
    pcStack_188 = (char *)0x715590;
    cVar2 = FUN_006d4590();
    if (cVar2 != '\0') {
      pcStack_188 = "Raw Handshake response:\n";
      puStack_18c = local_bc;
      pcStack_190 = (code *)0x7155b8;
      local_134 = FUN_0066e860();
      local_8 = 4;
      pcStack_188 = (char *)0x400;
      puStack_18c = (undefined1 *)0x7155f1;
      local_124 = local_134;
      FUN_006d4480();
      local_8 = 0xffffffff;
      ~basic_string<>();
      pcStack_188 = (char *)0x715613;
      basic_string<>();
      local_8 = 5;
      pcStack_188 = (char *)0x715632;
      FUN_006b7490();
      cVar2 = FUN_0041f890();
      local_109 = cVar2 == '\0';
      local_110 = (uint)(byte)local_109;
      local_8 = 0xffffffff;
      ~basic_string<>();
      if (local_109 != '\0') {
        pcStack_188 = (char *)0x715690;
        basic_string<>();
        local_8 = 6;
        pcStack_188 = (char *)0x7156ac;
        FUN_006b7490();
        pcStack_188 = local_ec;
        puStack_18c = (undefined1 *)0x7156b9;
        local_12c = FUN_006b6520();
        local_8._0_1_ = 7;
        pcStack_188 = (char *)0x400;
        puStack_18c = (undefined1 *)0x7156ef;
        local_11c = local_12c;
        FUN_006d4480();
        local_8 = CONCAT31(local_8._1_3_,6);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    local_140 = FUN_007205f0;
    local_13c = 0;
    pcStack_188 = (char *)0x715733;
    pcStack_188 = (char *)FUN_006e1540();
    local_8 = 8;
    puStack_18c = (undefined1 *)local_13c;
    pcStack_190 = local_140;
    puStack_194 = local_17c;
    uStack_198 = 0x715774;
    local_120 = pcStack_188;
    local_118 = pcStack_188;
    local_138 = FUN_006eadb0();
    local_8._0_1_ = 9;
    local_148 = (undefined1 *)&uStack_198;
    local_130 = local_138;
    local_14c = FUN_006eae00(local_138);
    uVar6 = FUN_004170c0();
    uVar7 = FUN_00430770(uVar6);
    FUN_006fff30(uVar7,uVar6);
    local_8 = CONCAT31(local_8._1_3_,8);
    ~input_processor<>();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

