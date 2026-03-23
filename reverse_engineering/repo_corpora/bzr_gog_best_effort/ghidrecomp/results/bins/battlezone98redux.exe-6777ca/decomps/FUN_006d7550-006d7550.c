
void FUN_006d7550(void)

{
  char cVar1;
  undefined1 local_3c [12];
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a048;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  FUN_006ab750(local_14);
  FUN_006bb2e0(local_2c,local_3c);
  local_8 = 0;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    basic_string<>(local_2c);
    local_30 = local_30 | 1;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    FUN_006d46a0(4,local_2c);
    basic_string<>("Unknown");
    local_30 = local_30 | 1;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

