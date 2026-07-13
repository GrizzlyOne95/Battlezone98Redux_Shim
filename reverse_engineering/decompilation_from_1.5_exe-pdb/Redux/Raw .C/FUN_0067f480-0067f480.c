
void FUN_0067f480(int param_1)

{
  uint uStack_200;
  undefined1 local_1c0 [36];
  undefined4 local_19c;
  undefined4 local_170;
  int local_f0;
  undefined4 local_e4;
  undefined1 local_a8 [48];
  undefined1 local_78 [80];
  char local_28 [16];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f7d1;
  local_10 = ExceptionList;
  uStack_200 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_200;
  ExceptionList = &local_10;
  local_f0 = param_1 + 0x74;
  local_18 = uStack_200;
  basic_string<>(local_f0);
  local_8 = 0;
  FUN_004222c0(local_1c0,local_78);
  local_8 = 0xffffffff;
  ~basic_string<>();
  sprintf(local_28,"%.*s.mesh",10,local_f0);
  local_e4 = 0;
  local_8 = 1;
  local_19c = basic_string<>(local_28);
  local_8._0_1_ = 2;
  local_170 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x17c))(local_a8);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_e4 = local_170;
  ~basic_string<>();
  FUN_0067f599();
  return;
}

