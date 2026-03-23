
_Ref_count_base * __fastcall FUN_006e87f0(_Ref_count_base *param_1)

{
  uint uVar1;
  int iVar2;
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
  *(undefined ***)param_1 =
       std::
       _Ref_count_obj<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
       ::vftable;
  iVar2 = forward<>(0x18,param_1 + 0xc,uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (iVar2 != 0) {
    basic_string<>();
  }
  ExceptionList = local_10;
  return param_1;
}

