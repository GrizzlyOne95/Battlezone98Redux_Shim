
undefined * FUN_006ca2e0(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008527ae;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2c3c & 1) == 0) {
    DAT_02cc2c3c = DAT_02cc2c3c | 1;
    local_8 = 0;
    std::allocator<char>::allocator<char>((allocator<char> *)&DAT_02cc2c4c);
  }
  ExceptionList = local_10;
  return &DAT_02cc2c4c;
}

