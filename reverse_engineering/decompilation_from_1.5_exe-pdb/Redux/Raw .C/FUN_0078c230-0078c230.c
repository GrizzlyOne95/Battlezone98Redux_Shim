
void __fastcall FUN_0078c230(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085eab6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((*(int *)(param_1 + 0x148) != 0) && (DAT_00917f90 != 0 || DAT_00917f94 != 0)) {
    FUN_00685580(100,local_14);
    uVar2 = FUN_00572790();
    (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))(uVar2);
    uVar1 = FUN_00577760();
    FUN_00482630(local_5c,uVar1);
    local_8 = 0;
    uVar2 = FUN_004b75b0();
    FUN_0073b940(local_74,uVar2);
    local_8._0_1_ = 1;
    uVar2 = FUN_0066e860(local_8c,"Connecting: ",local_5c);
    local_8._0_1_ = 2;
    uVar2 = FUN_0045f170(local_a4,uVar2,&DAT_0089dc98);
    local_8._0_1_ = 3;
    FUN_00426a20(local_2c,uVar2,local_74);
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 6;
    ~basic_string<>();
    uVar2 = FUN_0041f870();
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x3c))(uVar2);
    uVar2 = FUN_005726f0();
    FUN_00482630(local_44,uVar2);
    local_8._0_1_ = 7;
    uVar2 = FUN_0041f870();
    (**(code **)(**(int **)(param_1 + 0x150) + 0x3c))(uVar2);
    local_8._0_1_ = 6;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

