
void FUN_0080a540(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00864a20;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_00420f10(&stack0x0000000c);
  if (cVar1 != '\0') {
    uVar2 = FUN_00422e80();
    FUN_0080ad00(param_1,uVar2);
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  FUN_0080a603();
  return;
}

