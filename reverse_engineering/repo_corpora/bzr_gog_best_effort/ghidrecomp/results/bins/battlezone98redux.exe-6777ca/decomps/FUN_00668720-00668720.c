
void __fastcall FUN_00668720(Archive *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084e58a;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = Ogre76Archive::vftable;
  local_8 = 3;
  FUN_00417c60(uVar1);
  local_8._0_1_ = 2;
  FUN_00667210();
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00667840();
  local_8 = 0xffffffff;
  Ogre::Archive::~Archive(param_1);
  ExceptionList = local_10;
  return;
}

