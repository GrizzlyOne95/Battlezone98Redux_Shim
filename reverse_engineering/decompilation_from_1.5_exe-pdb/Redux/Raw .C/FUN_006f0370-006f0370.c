
_Ref_count_base * __thiscall
FUN_006f0370(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_28 [16];
  int local_18;
  _Ref_count_base *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854dec;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)local_14 =
       std::
       _Ref_count_obj<class_boost::asio::basic_waitable_timer<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>,class_boost::asio::waitable_timer_service<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>_>_>_>
       ::vftable;
  local_18 = forward<>(0x28,local_14 + 0x10,uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (local_18 != 0) {
    uVar2 = FUN_00417780(param_3);
    FUN_006fdc40(uVar2);
    puVar3 = local_28;
    FUN_00417780(param_2,puVar3);
    uVar2 = FUN_006f2800();
    FUN_006f3220(uVar2,puVar3);
  }
  ExceptionList = local_10;
  return local_14;
}

