
_Ref_count_base * __thiscall
FUN_00724a20(_Ref_count_base *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_50 [16];
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
  p_Stack_34 = (_Ref_count_base *)0x724a50;
  local_14 = param_1;
  std::_Ref_count_base::_Ref_count_base(param_1);
  local_8 = 0;
  *(undefined ***)local_14 = std::_Ref_count_obj<class_websocketpp::uri>::vftable;
  p_Stack_34 = local_14 + 0xc;
  uStack_38 = 0x4c;
  uStack_3c = 0x724a6e;
  local_18 = forward<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  if (local_18 != 0) {
    p_Stack_34 = (_Ref_count_base *)param_4;
    uStack_38 = 0x724a87;
    p_Stack_34 = (_Ref_count_base *)FUN_00417780();
    uStack_38 = param_3;
    uStack_3c = 0x724a94;
    uStack_38 = FUN_00417780();
    uStack_3c = param_2;
    uStack_40 = 0x724aa1;
    pbVar1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00417780();
    local_24 = abStack_50;
    local_28 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_50,pbVar1);
    FUN_006b59a0();
  }
  ExceptionList = local_10;
  return local_14;
}

