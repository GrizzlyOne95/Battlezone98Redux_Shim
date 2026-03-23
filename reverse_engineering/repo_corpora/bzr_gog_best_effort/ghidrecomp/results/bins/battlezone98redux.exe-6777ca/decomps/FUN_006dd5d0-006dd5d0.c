
void FUN_006dd5d0(undefined4 param_1)

{
  undefined1 local_64 [44];
  undefined1 local_38 [32];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853a68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_18 = enable_error_info<>(local_38,param_1);
  local_8 = 0;
  local_14 = local_18;
  enable_current_exception<>(local_64,local_18);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_64,(ThrowInfo *)&DAT_008d8474);
}

