
undefined * FUN_006ca350(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008527de;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2c1c & 1) == 0) {
    DAT_02cc2c1c = DAT_02cc2c1c | 1;
    local_8 = 0;
    std::allocator<char>::allocator<char>((allocator<char> *)&DAT_02cc2c64);
  }
  ExceptionList = local_10;
  return &DAT_02cc2c64;
}

