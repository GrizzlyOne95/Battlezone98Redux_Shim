
void FUN_00449df0(undefined4 param_1)

{
  undefined1 local_a4 [76];
  undefined1 local_58 [64];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846318;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_18 = enable_error_info<>(local_58,param_1);
  local_8 = 0;
  local_14 = local_18;
  enable_current_exception<>(local_a4,local_18);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_a4,(ThrowInfo *)&DAT_008d7b8c);
}

