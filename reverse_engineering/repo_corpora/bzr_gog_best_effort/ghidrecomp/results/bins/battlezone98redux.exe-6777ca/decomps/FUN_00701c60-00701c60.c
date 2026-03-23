
undefined4 __thiscall FUN_00701c60(int param_1,undefined4 param_2)

{
  shared_ptr<class___ExceptionPtr> local_18 [8];
  undefined4 local_10;
  uint local_c;
  int local_8;
  
  local_c = 0;
  local_8 = param_1;
  std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
            (local_18,(shared_ptr<class___ExceptionPtr> *)(param_1 + 0x1c));
  local_10 = FUN_0068b0a0();
  FID_conflict_operator_(local_10);
  FUN_006ca8c0();
  *(undefined4 *)(local_8 + 0x10) = 0;
  shared_ptr<>(local_18);
  local_c = local_c | 1;
  FUN_006ca8c0();
  return param_2;
}

