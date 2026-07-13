
void __fastcall FUN_007abd00(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  uint uVar5;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860a80;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  iVar2 = FUN_0041c1d0(uVar1);
  uVar5 = (uint)(iVar2 != 0);
  uVar3 = FUN_007c3cc0(uVar1,uVar5,uVar5);
  pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006cf480(uVar3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
  local_8 = 0;
  basic_string<>("leftjoy");
  local_8._0_1_ = 1;
  FUN_007abae0(local_2c,uVar5,local_44,*(undefined4 *)(param_1 + 0x170),
               *(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x178),
               *(undefined4 *)(param_1 + 0x17c),*(undefined4 *)(param_1 + 0x180),
               *(undefined4 *)(param_1 + 0x16c));
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>("rightjoy");
  local_8._0_1_ = 2;
  FUN_007abae0(local_2c,uVar5,local_74,*(undefined4 *)(param_1 + 0x188),
               *(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 400),
               *(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x198),
               *(undefined4 *)(param_1 + 0x184));
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>(&DAT_008713d4);
  local_8._0_1_ = 3;
  FUN_007abae0(local_2c,uVar5,local_5c,0,0,0,*(undefined4 *)(param_1 + 0x1a0),
               *(undefined4 *)(param_1 + 0x1a4),*(undefined4 *)(param_1 + 0x19c));
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

