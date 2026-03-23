
_Ref_count_base * __thiscall
FUN_00716570(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  uint uVar4;
  undefined4 uStack_40;
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
  p_Stack_38 = (_Ref_count_base *)0x7165a0;
  local_14 = param_1;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)local_14 =
       std::
       _Ref_count_obj<class_websocketpp::processor::hybi08<struct_websocketpp::config::asio_client>_>
       ::vftable;
  p_Stack_38 = local_14 + 0xc;
  uStack_3c = 100;
  uStack_40 = 0x7165be;
  local_18 = forward<>();
  local_8._0_1_ = 1;
  if (local_18 != 0) {
    p_Stack_38 = (_Ref_count_base *)param_5;
    uStack_3c = 0x7165d7;
    FUN_00417780();
    p_Stack_38 = (_Ref_count_base *)0x7165e1;
    p_Stack_38 = (_Ref_count_base *)FUN_006f2800();
    uStack_3c = param_4;
    uStack_40 = 0x7165eb;
    psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_00417780();
    local_28 = (undefined1 *)&uStack_40;
    local_2c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&uStack_40,psVar1);
    local_8._0_1_ = 2;
    local_20 = local_2c;
    pbVar2 = (byte *)FUN_00417780(param_3);
    uVar4 = (uint)*pbVar2;
    puVar3 = (undefined1 *)FUN_00417780(param_2,uVar4);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_0071bf40(*puVar3,uVar4);
  }
  ExceptionList = local_10;
  return local_14;
}

