
void __fastcall FUN_007ce580(int *param_1)

{
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *p_Var1;
  int iVar2;
  _ExceptionHolder *p_Var3;
  undefined4 uVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Var1 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_00764760(local_14);
  std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(p_Var1);
  iVar2 = FUN_004170c0();
  if ((iVar2 == 0) || ((uint)(iVar2 - param_1[0xa56]) < (uint)param_1[0xa53])) {
    param_1[0xa56] = 0;
  }
  (**(code **)(*(int *)param_1[0xa54] + 0x24))
            ((uint)param_1[0xa53] <= (uint)(iVar2 - param_1[0xa56]));
  (**(code **)(*(int *)param_1[0xa55] + 0x24))(param_1[0xa56] != 0);
  p_Var1 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_00764760();
  p_Var3 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(p_Var1);
  FUN_007ce770(local_2c,p_Var3);
  local_8 = 0;
  uVar4 = FUN_0041f870(3);
  (**(code **)(*param_1 + 0x3c))(uVar4);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

