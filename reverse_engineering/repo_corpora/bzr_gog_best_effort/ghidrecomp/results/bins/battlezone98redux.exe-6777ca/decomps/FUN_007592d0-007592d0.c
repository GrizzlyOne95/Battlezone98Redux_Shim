
char __thiscall FUN_007592d0(int *param_1,undefined4 param_2,int param_3,uint param_4,int param_5)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  ushort uVar6;
  undefined1 local_114 [32];
  basic_ostream<char,struct_std::char_traits<char>_> local_f4 [160];
  basic_ostream<char,struct_std::char_traits<char>_> *local_54;
  basic_ostream<char,struct_std::char_traits<char>_> *local_50;
  basic_ostream<char,struct_std::char_traits<char>_> *local_4c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_48;
  basic_ostream<char,struct_std::char_traits<char>_> *local_44;
  basic_ostream<char,struct_std::char_traits<char>_> *local_40;
  basic_ostream<char,struct_std::char_traits<char>_> *local_3c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_38;
  undefined *local_34;
  basic_ostream<char,struct_std::char_traits<char>_> *local_30;
  int local_2c;
  undefined1 local_25;
  int local_24;
  int local_20;
  uint local_1c;
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c87b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1[8] = param_1[8] + param_4;
  param_1[7] = param_1[7] + 1;
  local_18 = param_1;
  local_11 = (**(code **)(*param_1 + 0xc))(param_2,param_3,param_4,param_5,uVar1);
  if (DAT_00917f6c != 0) {
    local_20 = FUN_00764760();
    local_24 = 0;
    local_2c = 0;
    if (local_20 != 0) {
      local_24 = FUN_00746690(param_2);
      local_2c = FUN_0073bd10();
    }
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0x104) {
      local_54 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_54 = local_f4;
    }
    FUN_004bc590(local_54,"TX SRC ");
    if (local_24 == 0) {
      if (&stack0x00000000 == (undefined1 *)0x104) {
        local_30 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_30 = local_f4;
      }
      FUN_004bc590(local_30,&DAT_0089b76c);
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x104) {
        local_38 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_38 = local_f4;
      }
      uVar6 = *(ushort *)(local_24 + 0x28);
      pcVar5 = FUN_0056f740;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_38,&DAT_0088d764);
      pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar6);
    }
    if (&stack0x00000000 == (undefined1 *)0x104) {
      local_40 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_40 = local_f4;
    }
    FUN_004bc590(local_40," DST ");
    if (local_2c == 0) {
      if (&stack0x00000000 == (undefined1 *)0x104) {
        local_48 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_48 = local_f4;
      }
      FUN_004bc590(local_48,&DAT_0089b76c);
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x104) {
        local_50 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_50 = local_f4;
      }
      uVar6 = *(ushort *)(local_2c + 0x28);
      pcVar5 = FUN_0056f740;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_50,&DAT_0088d764);
      pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar6);
    }
    if (local_11 == '\0') {
      local_34 = &DAT_00884848;
    }
    else {
      local_34 = &DAT_00873e10;
    }
    if (&stack0x00000000 == (undefined1 *)0x104) {
      local_3c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_3c = local_f4;
    }
    uVar3 = FUN_007591f0(param_2,"  Sent: ",local_34," Packet: ");
    uVar3 = FUN_004bc590(local_3c,uVar3);
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_004bc590(uVar3);
    FUN_004bc590(uVar3);
    uVar3 = FUN_006dc270(&local_25,0x30);
    pcVar5 = FUN_006ab840;
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                       (local_f4,FUN_00574a10);
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
    FUN_006dc290(pbVar2,uVar3);
    for (local_1c = 0; local_1c < param_4; local_1c = local_1c + 1) {
      if (&stack0x00000000 == (undefined1 *)0x104) {
        local_44 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_44 = local_f4;
      }
      uVar1 = (uint)*(byte *)(param_3 + local_1c);
      uVar3 = std::setw(CONCAT44(2,local_114));
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(local_44,uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar1);
    }
    if (&stack0x00000000 == (undefined1 *)0x104) {
      local_4c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_4c = local_f4;
    }
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_4c," Send Type: ");
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,param_5);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_f4,FUN_004bc8c0);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar4);
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return local_11;
}

