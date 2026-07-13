
void FUN_006ccb70(void)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852c22;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  vector<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006cf440(9);
  uVar1 = basic_string<>("first");
  local_8._0_1_ = 1;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("second");
  local_8._0_1_ = 2;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("third");
  local_8._0_1_ = 3;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("fourth");
  local_8._0_1_ = 4;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("fifth");
  local_8._0_1_ = 5;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>(&DAT_008961a8);
  local_8._0_1_ = 6;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("before");
  local_8._0_1_ = 7;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>("after");
  local_8._0_1_ = 8;
  FUN_006cf320(uVar1);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar1 = basic_string<>(&DAT_00896254);
  local_8._0_1_ = 9;
  FUN_006cf320(uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

