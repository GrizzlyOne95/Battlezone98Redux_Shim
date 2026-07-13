
void FUN_0067ec70(int param_1)

{
  uint uStack_a0;
  undefined1 local_90 [8];
  undefined4 local_88;
  undefined4 local_80;
  int local_78;
  undefined4 local_70;
  int local_6c;
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  char local_38 [32];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f6e0;
  local_10 = ExceptionList;
  uStack_a0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_a0;
  ExceptionList = &local_10;
  local_6c = param_1;
  local_78 = *(int *)(*(int *)(param_1 + 0xc) + 0x34) + 0x84;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  local_18 = uStack_a0;
  basic_string<>(local_78);
  local_8 = 0;
  FUN_004222c0(local_90,local_68);
  local_8 = 0xffffffff;
  ~basic_string<>();
  sprintf(local_38,"%.*s.mesh",0x1a,local_78);
  local_70 = 0;
  local_8 = 1;
  local_88 = basic_string<>(local_38);
  local_8._0_1_ = 2;
  local_80 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x17c))(local_50);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_70 = local_80;
  ~basic_string<>();
  FUN_0067ed9d();
  return;
}

