
/* WARNING: Removing unreachable block (ram,0x0075a7f9) */

void FUN_0075a710(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 byte param_5,undefined4 param_6,undefined4 param_7)

{
  uint uVar1;
  char *_Source;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  undefined4 uVar5;
  ushort uVar6;
  size_t _Count;
  undefined1 *puVar7;
  basic_ostream<char,struct_std::char_traits<char>_> local_254 [176];
  undefined1 auStack_1a4 [160];
  undefined1 local_104 [16];
  undefined1 local_f4 [8];
  undefined1 local_ec [8];
  undefined1 *local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  int local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 local_c8;
  undefined1 *local_c4;
  undefined1 local_bd;
  int local_bc;
  char *local_b8;
  char local_b1;
  undefined1 local_b0 [24];
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  byte local_68 [14];
  undefined1 local_5a [4];
  char local_56;
  undefined1 auStack_55 [62];
  undefined1 uStack_17;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ca34;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  memset(local_68,0,0x52);
  local_68[0] = local_68[0] | 0x40;
  local_68[1] = local_68[1] | param_5;
  FUN_0073a9f0(local_80);
  local_8 = 0;
  param_6 = 0;
  FUN_006dc210(&param_3,local_68 + 2,0,0,uVar1);
  FUN_007605e0(&param_7,local_5a,0,0);
  _Count = 0x40;
  _Source = (char *)FUN_0041f870();
  strncat(&local_56,_Source,_Count);
  local_c8 = 0x51;
  uStack_17 = 0;
  local_b8 = &local_56;
  local_e4 = auStack_55;
  do {
    local_b1 = *local_b8;
    local_b8 = local_b8 + 1;
  } while (local_b1 != '\0');
  local_d4 = (int)local_b8 - (int)local_e4;
  local_cc = local_d4 + 0x13;
  if (DAT_008eda28 != 0) {
    FUN_00574400(3,1);
    local_8._0_1_ = 1;
    for (local_bc = 0; local_bc < local_cc; local_bc = local_bc + 1) {
      uVar6 = (ushort)local_68[local_bc];
      uVar2 = std::setw(CONCAT44(2,local_104));
      pcVar4 = FUN_006ab840;
      uVar2 = FUN_006dc270(&local_bd,0x30,FUN_006ab840,uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                         (local_254,FUN_00574a10);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006dc290(pbVar3,uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,uVar6);
    }
    FUN_00574400(3,1);
    local_8._0_1_ = 2;
    if (&stack0x00000000 == (undefined1 *)0x1b4) {
      local_c4 = (undefined1 *)0x0;
    }
    else {
      local_c4 = auStack_1a4;
    }
    FUN_006da360(local_c4,param_2);
    local_e0 = GetPolicy(local_98);
    local_8._0_1_ = 3;
    local_d8 = local_e0;
    local_dc = GetPolicy(local_b0);
    local_8._0_1_ = 4;
    local_d0 = local_dc;
    uVar2 = FUN_0041f870();
    uVar2 = FUN_0041f870(uVar2);
    FUN_007d6a70("BZRNet P2P CON Sent Packet (%u,%u) to %s: %s\n",param_6,param_7,uVar2);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    FUN_00417f10();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
  }
  FUN_004fbb60();
  puVar7 = local_ec;
  uVar5 = 0;
  uVar2 = FUN_00760630(local_f4,local_68,local_cc,param_2,0,puVar7);
  FUN_006dc2e0(uVar2,param_2,uVar5,puVar7);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

