
void FUN_0075a490(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  code *pcVar3;
  undefined4 uVar4;
  ushort uVar5;
  undefined1 *puVar6;
  basic_ostream<char,struct_std::char_traits<char>_> local_1e4 [176];
  undefined1 auStack_134 [160];
  undefined1 local_94 [16];
  undefined1 local_84 [8];
  undefined1 local_7c [8];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 *local_64;
  undefined1 local_5d;
  uint local_5c;
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c9d6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_28 = (uint)CONCAT11(param_5,0x40);
  FUN_006dc210(&param_3,(int)&local_28 + 2,0,0,local_14);
  FUN_007605e0(&param_6,(int)&local_20 + 2,0,0);
  FUN_007605e0(&param_7,(int)&local_1c + 2,0,0);
  if (2 < DAT_008eda28) {
    FUN_00574400(3,1);
    local_8 = 0;
    for (local_5c = 0; local_5c < 0x12; local_5c = local_5c + 1) {
      uVar5 = (ushort)*(byte *)((int)&local_28 + local_5c);
      uVar1 = std::setw(CONCAT44(2,local_94));
      pcVar3 = FUN_006ab840;
      uVar1 = FUN_006dc270(&local_5d,0x30,FUN_006ab840,uVar1);
      pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                         (local_1e4,FUN_00574a10);
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006dc290(pbVar2,uVar1);
      pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar3);
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar5);
    }
    FUN_00574400(3,1);
    local_8._0_1_ = 1;
    if (&stack0x00000000 == (undefined1 *)0x144) {
      local_64 = (undefined1 *)0x0;
    }
    else {
      local_64 = auStack_134;
    }
    FUN_006da360(local_64,param_2);
    local_70 = GetPolicy(local_58);
    local_8._0_1_ = 2;
    local_6c = local_70;
    local_74 = GetPolicy(local_40);
    local_8._0_1_ = 3;
    local_68 = local_74;
    uVar1 = FUN_0041f870();
    uVar1 = FUN_0041f870(uVar1);
    FUN_007d6a70("BZRNet P2P BAS Sent Packet (%u,%u) to %s: %s\n",param_6,param_7,uVar1);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  FUN_004fbb60();
  puVar6 = local_7c;
  uVar4 = 0;
  uVar1 = FUN_006dc2b0(local_84,&local_28,param_2,0,puVar6);
  FUN_006dc2e0(uVar1,param_2,uVar4,puVar6);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

