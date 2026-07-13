
undefined4 * __thiscall FUN_006e4a60(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uStack_34;
  undefined1 *puStack_30;
  uint uStack_2c;
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined1 local_10 [4];
  undefined4 local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 100) = param_3;
  uStack_2c = param_3;
  puStack_30 = local_10;
  uStack_34 = 0x6e4a88;
  local_8 = param_1;
  uStack_2c = select_on_container_copy_construction();
  puStack_30 = local_28;
  uStack_34 = 0x6e4a95;
  uStack_2c = FUN_006f1620();
  puStack_30 = (undefined1 *)0x6e4aaa;
  local_c = uStack_2c;
  FID_conflict_operator_();
  uStack_2c = 0x6e4ab2;
  FUN_006ca8c0();
  uStack_2c = (uint)*(byte *)(local_8 + 0x38);
  local_14 = (undefined1 *)&uStack_34;
  local_18 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&uStack_34,
                        (shared_ptr<class___ExceptionPtr> *)(local_8 + 0x68));
  FUN_006bb4e0(&local_20,param_3);
  *param_2 = local_20;
  param_2[1] = local_1c;
  return param_2;
}

