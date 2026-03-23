
void FUN_006c4c50(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined1 *puVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined1 auStack_1b0 [176];
  undefined1 local_100 [8];
  undefined1 local_f8 [16];
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c4;
  undefined1 *local_c0;
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
  puStack_c = &LAB_008520b2;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 != '\0') {
    FUN_00574400(3,1);
    local_8 = 0;
    FUN_006cc0e0();
    local_8._0_1_ = 1;
    basic_string<>(&DAT_0087d178);
    local_8._0_1_ = 2;
    uVar2 = basic_string<>("SetLobbyData");
    local_8._0_1_ = 3;
    local_dc = uVar2;
    local_d8 = uVar2;
    FUN_006cc100(local_2c);
    FUN_006dc070(uVar2);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("content");
    local_8._0_1_ = 4;
    uVar2 = FUN_006cc0e0();
    local_8._0_1_ = 5;
    local_d4 = uVar2;
    local_d0 = uVar2;
    FUN_006cc100(local_44);
    uVar2 = FUN_006dc0c0(uVar2);
    local_c4 = FUN_006db8f0(uVar2);
    local_8._0_1_ = 4;
    FUN_006c3d30();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>(&DAT_0089867c);
    local_8._0_1_ = 6;
    FUN_006cc100(local_5c);
    FUN_006dc0a0(param_1);
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("value");
    local_8._0_1_ = 7;
    FUN_006cc100(local_74);
    FUN_006dc0a0(param_2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    if (&stack0x00000000 == (undefined1 *)0x1c0) {
      local_c0 = (undefined1 *)0x0;
    }
    else {
      local_c0 = auStack_1b0;
    }
    FUN_007d7970(local_c0,local_f8,0,2);
    if (2 < DAT_008eda28) {
      local_e8 = GetPolicy(local_8c);
      local_8._0_1_ = 8;
      pcVar4 = FUN_004bc8c0;
      local_e0 = local_e8;
      FUN_0081e820("WebSocket Message Sent:\n",local_e8);
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar4);
      local_8._0_1_ = 1;
      ~basic_string<>();
    }
    uVar2 = GetPolicy(local_a4);
    local_8._0_1_ = 9;
    uVar5 = 1;
    puVar3 = local_100;
    local_e4 = uVar2;
    local_cc = uVar2;
    FUN_00421ec0(puVar3,uVar2,1);
    FUN_006da6b0(puVar3,uVar2,uVar5);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c3d30();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

