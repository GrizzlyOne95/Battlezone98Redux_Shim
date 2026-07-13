
void FUN_006c31e0(void)

{
  bool bVar1;
  char cVar2;
  shared_ptr<class___ExceptionPtr> local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851cd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = &stack0xffffffcc;
  local_1c = shared_ptr<>(&stack0x00000004);
  local_20 = FUN_006cbe40(local_28);
  bVar1 = std::operator==<class___ExceptionPtr,class___ExceptionPtr>
                    (local_28,(shared_ptr<class___ExceptionPtr> *)(local_14 + 0x2e0));
  if (bVar1) {
    cVar2 = FUN_006ab7d0();
    if (cVar2 != '\0') {
      *(undefined1 *)(local_14 + 0x31c) = 0;
    }
  }
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

