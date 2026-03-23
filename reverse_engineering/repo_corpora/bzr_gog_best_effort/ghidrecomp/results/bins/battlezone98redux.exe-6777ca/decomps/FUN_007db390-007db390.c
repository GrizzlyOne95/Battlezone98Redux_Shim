
void FUN_007db390(undefined4 param_1,undefined4 param_2,
                 List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
                 *param_3)

{
  List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
  *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ed38;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = (List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
          *)FUN_007dce30(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  Concurrency::details::
  List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
  ::Swap(this,param_3);
  local_8 = 0xffffffff;
  FUN_006670f0();
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_1,param_2,param_2);
  ExceptionList = local_10;
  return;
}

