
_Ref_count_base * __thiscall
FUN_006fe3f0(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  _Ref_count_base *p_Stack_34;
  uint uStack_30;
  undefined4 local_28;
  undefined1 *local_24;
  int local_18;
  _Ref_count_base *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855efc;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Stack_34 = (_Ref_count_base *)0x6fe420;
  local_14 = param_1;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)local_14 =
       std::
       _Ref_count_obj<class_websocketpp::message_buffer::message<class_websocketpp::message_buffer::alloc::con_msg_manager>_>
       ::vftable;
  p_Stack_34 = local_14 + 0xc;
  uStack_38 = 0x58;
  uStack_3c = 0x6fe43e;
  local_18 = forward<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  if (local_18 != 0) {
    p_Stack_34 = (_Ref_count_base *)param_4;
    uStack_38 = 0x6fe457;
    puVar1 = (undefined4 *)FUN_00417780();
    p_Stack_34 = (_Ref_count_base *)*puVar1;
    uStack_38 = param_3;
    uStack_3c = 0x6fe466;
    puVar1 = (undefined4 *)FUN_00417780();
    uStack_38 = *puVar1;
    uStack_3c = param_2;
    uStack_40 = 0x6fe475;
    uVar2 = FUN_00417780();
    local_24 = (undefined1 *)&uStack_40;
    local_28 = shared_ptr<>(uVar2);
    FUN_007006b0();
  }
  ExceptionList = local_10;
  return local_14;
}

