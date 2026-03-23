
void __thiscall
FUN_00667700(Archive *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
            Archive param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e35a;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  Ogre::Archive::Archive(param_1,param_2,param_3);
  local_8 = 0;
  *(undefined ***)param_1 = Ogre76Archive::vftable;
  FUN_0066a410(uVar1);
  local_8._0_1_ = 1;
  basic_string<>();
  local_8._0_1_ = 2;
  FUN_006671f0();
  local_8._0_1_ = 3;
  param_1[0x34] = param_4;
  FUN_00426a60(&DAT_02cf0000,0);
  local_8._0_1_ = 4;
  FUN_004fed70(param_2);
  uVar2 = FUN_00417fd0(local_44);
  local_8._0_1_ = 5;
  FUN_006679c0(0xffffffff,uVar2);
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_004180b0();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

