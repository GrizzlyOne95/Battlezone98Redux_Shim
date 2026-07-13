
undefined4 FUN_0073c0b0(undefined4 param_1,char param_2)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  basic_ostream<char,struct_std::char_traits<char>_> local_f0 [160];
  undefined *local_50;
  uint local_4c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_48;
  basic_ostream<char,struct_std::char_traits<char>_> *local_44;
  undefined *local_40;
  undefined *local_3c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_38;
  basic_ostream<char,struct_std::char_traits<char>_> *local_34;
  basic_ostream<char,struct_std::char_traits<char>_> *local_30;
  undefined *local_2c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_28;
  basic_ostream<char,struct_std::char_traits<char>_> *local_24;
  basic_ostream<char,struct_std::char_traits<char>_> *local_20;
  undefined *local_1c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_18;
  uint *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a97b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  uVar3 = 0x2a;
  pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_f0,*local_14);
  FUN_006d9650(pbVar2,uVar3,uVar1);
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_38 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_38 = local_f0;
  }
  uVar4 = 0x2a;
  uVar3 = FUN_00574730(local_38,local_14 + 1,0x2a);
  FUN_006d9650(uVar3,uVar4,uVar1);
  if ((char)local_14[7] == '\0') {
    if (param_2 == '\0') {
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_48 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_48 = local_f0;
      }
      FUN_004bc590(local_48,&DAT_0089acf4);
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_20 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_20 = local_f0;
      }
      FUN_004bc590(local_20,&DAT_0089acf8);
    }
  }
  else {
    uVar3 = 0x2a;
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                       (local_f0,local_14[8]);
    FUN_006d9650(pbVar2,uVar3);
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_28 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_28 = local_f0;
  }
  uVar3 = FUN_00574730(local_28,local_14 + 9,0x2a);
  FUN_006d9650(uVar3);
  if ((char)local_14[0xf] == '\0') {
    local_40 = &DAT_0089acfc;
  }
  else {
    local_40 = &DAT_0089ad00;
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_30 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_30 = local_f0;
  }
  FUN_004bc590(local_30,local_40);
  if (*(char *)((int)local_14 + 0x3d) == '\0') {
    local_50 = &DAT_0089acfc;
  }
  else {
    local_50 = &DAT_0089ad00;
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_18 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_18 = local_f0;
  }
  FUN_004bc590(local_18,local_50);
  if (*(char *)((int)local_14 + 0x3e) == '\0') {
    local_1c = &DAT_0089acfc;
  }
  else {
    local_1c = &DAT_0089ad00;
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_24 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_24 = local_f0;
  }
  FUN_004bc590(local_24,local_1c);
  uVar3 = 0x2a;
  pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                     (local_f0,local_14[0x10]);
  FUN_006d9650(pbVar2,uVar3);
  uVar3 = 0x2a;
  pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                     (local_f0,local_14[0x11]);
  FUN_006d9650(pbVar2,uVar3);
  uVar3 = 0x2a;
  pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                     (local_f0,local_14[0x12]);
  FUN_006d9650(pbVar2,uVar3);
  if ((char)local_14[0x13] == '\0') {
    local_2c = &DAT_0089acfc;
  }
  else {
    local_2c = &DAT_0089ad00;
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_34 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_34 = local_f0;
  }
  FUN_004bc590(local_34,local_2c);
  uVar3 = 0x2a;
  pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                     (local_f0,local_14[0x14]);
  FUN_006d9650(pbVar2,uVar3);
  if ((char)local_14[0x15] == '\0') {
    local_3c = &DAT_0089acfc;
  }
  else {
    local_3c = &DAT_0089ad00;
  }
  if (&stack0x00000000 == (undefined1 *)0x100) {
    local_44 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_44 = local_f0;
  }
  FUN_004bc590(local_44,local_3c);
  GetPolicy(param_1);
  local_4c = local_4c | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return param_1;
}

