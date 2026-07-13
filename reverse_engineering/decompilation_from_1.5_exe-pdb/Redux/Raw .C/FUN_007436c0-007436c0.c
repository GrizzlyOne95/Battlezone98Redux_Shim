
void FUN_007436c0(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  code *pcVar5;
  undefined1 auStack_330 [160];
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined *local_280;
  int local_27c;
  undefined1 *local_278;
  int local_274;
  int *local_270;
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
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
  puStack_c = &LAB_0085b363;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_27c = FUN_007659f0(local_14);
  if (local_27c != 0) {
    FUN_0073bb30();
  }
  local_270[0xe] = 1;
  FUN_00741e80(local_ec,local_270 + 0x22);
  local_8 = 0;
  basic_string<>(&DAT_00879d2c);
  local_8._0_1_ = 1;
  (**(code **)(*local_270 + 0x20))(param_1,local_74,local_ec);
  local_8._0_1_ = 0;
  ~basic_string<>();
  if ((char)local_270[0x18] == '\0') {
    local_280 = &DAT_00873ef0;
  }
  else {
    local_280 = &DAT_00873c74;
  }
  basic_string<>(local_280);
  local_8._0_1_ = 2;
  basic_string<>("gameType");
  local_8._0_1_ = 3;
  (**(code **)(*local_270 + 0x20))(param_1,local_2c,local_44);
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_274 = FUN_007470b0(param_1,0);
  if (local_274 == 0) {
    local_28c = FUN_0073cc40();
    local_8._0_1_ = 4;
    local_288 = local_28c;
    FUN_00747db0(local_28c);
    local_8._0_1_ = 0;
    FUN_0073cdf0();
    local_274 = FUN_0045e220();
    *(undefined4 *)(local_274 + 0x10) = *param_1;
    *(undefined4 *)(local_274 + 0x14) = param_1[1];
    *(undefined4 *)(local_274 + 0x18) = param_1[2];
    *(undefined4 *)(local_274 + 0x1c) = param_1[3];
    FUN_00743f40(local_274,1);
    pcVar5 = FUN_004bc8c0;
    pcVar4 = FUN_0056f740;
    FUN_0081e820("Added lobby : ",local_274 + 0x68,&DAT_00896ce8,local_274 + 0x10);
    uVar2 = FUN_0081e660();
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_00574730(uVar2);
    uVar2 = FUN_004bc590(uVar2);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  }
  else {
    FUN_00743f40(local_274,1);
  }
  *(undefined1 *)((int)local_270 + 0x21) = *(undefined1 *)(local_274 + 0xb0);
  pcVar5 = FUN_004bc8c0;
  pcVar4 = FUN_0056f740;
  FUN_0081e820("Setting lobby : ",local_274 + 0x68,&DAT_00896ce8,local_274 + 0x10,FUN_0056f740,
               " to GameVersion ",PTR_s_2_2_301_008eda3c);
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_00574730(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
  uVar2 = FUN_004bc590(pbVar3);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  if (*(char *)(local_274 + 0xb0) == '\0') {
    FUN_00742090(local_274);
  }
  else {
    basic_string<>(&DAT_008922f0);
    local_8._0_1_ = 5;
    basic_string<>("gameSettings");
    local_8._0_1_ = 6;
    (**(code **)(*local_270 + 0x20))(param_1,local_a4,local_d4);
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 0;
    ~basic_string<>();
    basic_string<>(PTR_s_2_2_301_008eda3c);
    local_8._0_1_ = 7;
    basic_string<>("GameVersion");
    local_8._0_1_ = 8;
    (**(code **)(*local_270 + 0x20))(param_1,local_5c,local_8c);
    local_8._0_1_ = 7;
    ~basic_string<>();
    local_8._0_1_ = 0;
    ~basic_string<>();
  }
  FUN_00742900(local_274);
  *(undefined1 *)(local_274 + 0xb5) = 1;
  if ((*(char *)((int)local_270 + 0x62) != '\0') && (*(char *)(local_274 + 0xb5) != '\0')) {
    cVar1 = FUN_0056f780(local_270 + 10);
    if ((cVar1 != '\0') && (*(char *)(local_274 + 0xb4) != '\0')) {
      *(undefined1 *)(local_274 + 0xb5) = 0;
      *(undefined1 *)((int)local_270 + 0x62) = 0;
      FUN_00574400(3,1);
      local_8._0_1_ = 9;
      if (&stack0x00000000 == (undefined1 *)0x340) {
        local_278 = (undefined1 *)0x0;
      }
      else {
        local_278 = auStack_330;
      }
      FUN_007647a0();
      uVar2 = FUN_00583e30();
      FUN_0073ba70(local_278,uVar2);
      local_290 = GetPolicy(local_11c);
      local_8._0_1_ = 10;
      local_284 = local_290;
      uVar2 = FUN_0041f870();
      basic_string<>(uVar2);
      local_8._0_1_ = 0xb;
      basic_string<>("friendID");
      local_8._0_1_ = 0xc;
      (**(code **)(*local_270 + 0x1c))(local_270 + 10,local_bc,local_104);
      local_8._0_1_ = 0xb;
      ~basic_string<>();
      local_8._0_1_ = 10;
      ~basic_string<>();
      local_8._0_1_ = 9;
      ~basic_string<>();
      FUN_007464e0(4);
      FUN_00795c90();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
    }
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

