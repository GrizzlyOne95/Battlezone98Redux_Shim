
void __thiscall FUN_008440f0(int param_1,undefined4 param_2)

{
  code *pcVar1;
  uint uVar2;
  DWORD DVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *local_a0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_9c [16];
  undefined4 local_8c;
  undefined4 local_88;
  undefined **local_84 [3];
  DWORD local_78;
  undefined4 local_74;
  undefined1 local_70;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined1 local_28 [24];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865f2e;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_a0;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xffffff54;
  ExceptionList = &local_c;
  DVar3 = GetLastError();
  local_88 = 0xf;
  local_8c = 0;
  local_9c[0] = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            (local_9c,"boost::random_device: ",0x16);
  local_4 = 0;
  uVar4 = FUN_0045f170(local_58,local_9c,param_2,uVar2);
  local_4._0_1_ = 1;
  uVar4 = FUN_0045f170(local_28,uVar4," Cryptographic Service Provider ");
  local_4._0_1_ = 2;
  pcVar5 = (char *)FUN_00426a20(local_40,uVar4,param_1 + 4);
  local_4._0_1_ = 3;
  local_74 = FUN_0083e820();
  if (0xf < *(uint *)(pcVar5 + 0x14)) {
    pcVar5 = *(char **)pcVar5;
  }
  local_a0 = pcVar5;
  std::exception::exception((exception *)local_84,&local_a0);
  local_84[0] = boost::system::system_error::vftable;
  local_5c = 0xf;
  local_60 = 0;
  local_70 = 0;
  local_4 = CONCAT31(local_4._1_3_,4);
  local_78 = DVar3;
  FUN_006d89d0(local_84);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

