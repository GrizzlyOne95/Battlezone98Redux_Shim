
void FUN_007582e0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined4 *puVar6;
  undefined1 auStack_104 [160];
  undefined1 local_64 [12];
  undefined4 local_58;
  undefined4 local_54;
  undefined1 *local_50;
  undefined1 *local_4c;
  int *local_48;
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c70b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0x114) {
    local_4c = (undefined1 *)0x0;
  }
  else {
    local_4c = auStack_104;
  }
  FUN_00764760(uVar2);
  iVar3 = FUN_0056f900();
  uVar4 = FUN_004bc590(local_4c,"-connect-galaxy-lobby=",iVar3 + 0x10);
  FUN_0073ba70(uVar4);
  FUN_00764760();
  pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00754c90();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar5);
  local_8 = CONCAT31(local_8._1_3_,1);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    if (&stack0x00000000 == (undefined1 *)0x114) {
      local_50 = (undefined1 *)0x0;
    }
    else {
      local_50 = auStack_104;
    }
    uVar4 = FUN_004bc590(local_50,&DAT_008848ac,local_2c);
    FUN_00574730(uVar4);
  }
  local_48 = (int *)FUN_006aa1d0();
  local_58 = GetPolicy(local_44);
  local_8._0_1_ = 2;
  local_54 = local_58;
  uVar4 = FUN_0041f870();
  puVar6 = (undefined4 *)FUN_0073a970(local_64);
  (**(code **)(*local_48 + 0xc4))(*puVar6,puVar6[1],uVar4);
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

