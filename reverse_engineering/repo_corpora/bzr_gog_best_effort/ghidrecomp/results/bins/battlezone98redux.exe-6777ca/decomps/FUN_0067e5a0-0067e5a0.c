
void FUN_0067e5a0(undefined4 param_1,undefined4 param_2)

{
  uint uStack_130;
  undefined1 local_100 [32];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_b8;
  undefined1 local_b0 [48];
  undefined1 local_80 [72];
  char local_38 [32];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f69a;
  local_10 = ExceptionList;
  uStack_130 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_130;
  ExceptionList = &local_10;
  local_18 = uStack_130;
  basic_string<>(param_2);
  local_8 = 0;
  FUN_004222c0(local_100,local_80);
  local_8 = 0xffffffff;
  ~basic_string<>();
  sprintf(local_38,"%.*s.mesh",0x1a,param_2);
  local_b8 = 0;
  local_8 = 1;
  local_e0 = basic_string<>(local_38);
  local_8._0_1_ = 2;
  local_dc = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x17c))(local_b0);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_b8 = local_dc;
  ~basic_string<>();
  FUN_0067e6a8();
  return;
}

