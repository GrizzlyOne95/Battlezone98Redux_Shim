
void FUN_004485d0(int param_1,int param_2)

{
  undefined1 local_24 [4];
  refcount_ptr<struct_boost::exception_detail::error_info_container> *local_20;
  refcount_ptr<struct_boost::exception_detail::error_info_container> *local_1c;
  refcount_ptr<struct_boost::exception_detail::error_info_container> local_18 [4];
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846100;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00423890(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  local_14 = (int *)get();
  if (local_14 != (int *)0x0) {
    local_20 = (refcount_ptr<struct_boost::exception_detail::error_info_container> *)
               (**(code **)(*local_14 + 0x14))(local_24);
    local_8._0_1_ = 1;
    local_1c = local_20;
    boost::exception_detail::refcount_ptr<struct_boost::exception_detail::error_info_container>::
    operator=(local_18,local_20);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00449830();
  }
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
  boost::exception_detail::refcount_ptr<struct_boost::exception_detail::error_info_container>::
  operator=((refcount_ptr<struct_boost::exception_detail::error_info_container> *)(param_1 + 4),
            local_18);
  local_8 = 0xffffffff;
  FUN_00449830();
  ExceptionList = local_10;
  return;
}

