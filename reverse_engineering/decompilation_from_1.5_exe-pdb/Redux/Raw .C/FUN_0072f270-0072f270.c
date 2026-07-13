
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __fastcall
FUN_0072f270(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1)

{
  allocator<char> *paVar1;
  undefined1 *puVar2;
  allocator<char> local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859bf8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  paVar1 = (allocator<char> *)std::allocator<char>::allocator<char>(&local_12);
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>(param_1,paVar1)
  ;
  FID_conflict__Tidy();
  puVar2 = (undefined1 *)_Iter_cat<>();
  local_11 = *puVar2;
  FUN_004bbb20();
  local_8._0_1_ = 2;
  FUN_004bbb20(&stack0x00000004);
  local_8._0_1_ = 1;
  FUN_00731270();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return param_1;
}

