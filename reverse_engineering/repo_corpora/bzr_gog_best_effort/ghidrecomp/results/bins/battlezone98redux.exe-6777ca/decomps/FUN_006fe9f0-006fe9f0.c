
_Ref_count_base * __thiscall FUN_006fe9f0(_Ref_count_base *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008547ec;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = std::_Ref_count_obj<class_boost::asio::io_service::strand>::vftable;
  iVar2 = forward<>(8,param_1 + 0xc,uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (iVar2 != 0) {
    FUN_00417780(param_2);
    uVar3 = FUN_006f2800();
    FUN_006b4680(uVar3);
  }
  ExceptionList = local_10;
  return param_1;
}

