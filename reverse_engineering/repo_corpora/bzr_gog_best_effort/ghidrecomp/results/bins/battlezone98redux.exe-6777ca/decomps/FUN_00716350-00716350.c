
_Ref_count_base * __thiscall
FUN_00716350(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  byte *pbVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 uStack_3c;
  _Ref_count_base *p_Stack_38;
  uint uStack_34;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_20;
  int local_18;
  _Ref_count_base *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858144;
  local_10 = ExceptionList;
  uStack_34 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Stack_38 = (_Ref_count_base *)0x716380;
  local_14 = param_1;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)local_14 =
       std::
       _Ref_count_obj<class_websocketpp::processor::hybi00<struct_websocketpp::config::asio_client>_>
       ::vftable;
  p_Stack_38 = local_14 + 0xc;
  uStack_3c = 0x2c;
  local_18 = forward<>();
  local_8._0_1_ = 1;
  if (local_18 != 0) {
    p_Stack_38 = (_Ref_count_base *)param_4;
    uStack_3c = 0x7163b7;
    psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_00417780();
    local_28 = (undefined1 *)&uStack_3c;
    local_2c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&uStack_3c,psVar1);
    local_8._0_1_ = 2;
    local_20 = local_2c;
    pbVar2 = (byte *)FUN_00417780(param_3);
    uVar3 = (uint)*pbVar2;
    puVar4 = (undefined1 *)FUN_00417780(param_2,uVar3);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_0071bdf0(*puVar4,uVar3);
  }
  ExceptionList = local_10;
  return local_14;
}

