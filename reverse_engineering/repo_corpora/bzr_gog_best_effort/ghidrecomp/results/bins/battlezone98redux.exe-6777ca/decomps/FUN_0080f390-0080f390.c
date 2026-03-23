
void FUN_0080f390(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  CCachedDataPathProperty local_fc [104];
  undefined1 local_94 [52];
  undefined1 local_60 [52];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864c15;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("difference");
  local_8 = 1;
  uVar2 = FUN_0080f590(local_60,param_2);
  local_8._0_1_ = 2;
  uVar3 = FUN_008104a0(local_94,param_2);
  local_8._0_1_ = 3;
  uVar2 = FUN_00810540(local_fc,uVar3,uVar2,uVar1);
  local_8._0_1_ = 4;
  FUN_00810580(local_2c,uVar2);
  local_8._0_1_ = 3;
  CCachedDataPathProperty::~CCachedDataPathProperty(local_fc);
  local_8._0_1_ = 2;
  FUN_00800170();
  local_8._0_1_ = 1;
  FUN_00800170();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

