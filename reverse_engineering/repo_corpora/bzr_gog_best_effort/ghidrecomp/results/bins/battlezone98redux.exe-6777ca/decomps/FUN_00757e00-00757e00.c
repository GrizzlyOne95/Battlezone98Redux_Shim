
void FUN_00757e00(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int local_134 [48];
  undefined1 local_74 [23];
  char local_5d;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c683;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0073a6b0(local_14);
  basic_string<>();
  local_8 = 0;
  basic_string<>(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_004203f0(local_5c,3,1);
  local_8._0_1_ = 3;
  ~basic_string<>();
  FUN_004272a0(local_134,local_44,0x3d);
  FUN_0073ba90(local_134,local_74);
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,4);
  bVar1 = std::ios_base::eof((ios_base *)((int)local_134 + *(int *)(local_134[0] + 4)));
  if (!bVar1) {
    local_5d = ' ';
    std::basic_istream<char,struct_std::char_traits<char>_>::get
              ((basic_istream<char,struct_std::char_traits<char>_> *)local_134,&local_5d);
    if (local_5d == ',') {
      FUN_004272a0(local_134,local_2c,0);
    }
  }
  uVar2 = FUN_0073a6e0(param_1);
  puVar4 = local_2c;
  puVar3 = local_74;
  FUN_00764760(puVar3,puVar4,uVar2);
  FUN_007408c0(puVar3,puVar4,uVar2);
  local_8._0_1_ = 3;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00417f10();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

