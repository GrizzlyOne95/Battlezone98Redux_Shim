
void FUN_006cbe40(void)

{
  char cVar1;
  undefined1 local_58 [20];
  uint local_44;
  undefined1 local_40 [44];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852aa0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_44 = 0;
  local_8 = 0;
  FUN_006ab750();
  shared_ptr<>(&stack0x00000008);
  FUN_006cfe00(local_58);
  local_8._0_1_ = 1;
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    FUN_006b5120();
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_40,(ThrowInfo *)&DAT_008d8184);
  }
  shared_ptr<>();
  local_44 = local_44 | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

