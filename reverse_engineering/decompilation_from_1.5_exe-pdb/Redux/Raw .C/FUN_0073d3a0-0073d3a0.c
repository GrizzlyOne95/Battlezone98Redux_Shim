
void FUN_0073d3a0(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_e4 [176];
  undefined4 local_34;
  int *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ab43;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_004203f0(param_1,3,1);
  local_8 = 0;
  basic_string<>(uVar2);
  local_8._0_1_ = 1;
  while( true ) {
    local_30 = (int *)FUN_004272a0(local_e4,local_2c,param_2);
    bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_30 + *(int *)(*local_30 + 4)));
    if (!bVar1) break;
    FUN_006cae50(local_2c);
  }
  local_34 = param_3;
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

