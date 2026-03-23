
undefined4 * __thiscall FUN_006ae240(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008502fb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 1));
  local_8 = 0;
  *param_1 = boost::asio::io_service::service::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 1));
  param_1[3] = param_2;
  param_1[4] = 0;
  ExceptionList = local_10;
  return param_1;
}

