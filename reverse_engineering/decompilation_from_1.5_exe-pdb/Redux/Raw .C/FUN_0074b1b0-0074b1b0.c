
void FUN_0074b1b0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085bba0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_00420f10(&stack0x0000000c);
  if (cVar1 != '\0') {
    uVar2 = FUN_00422e80();
    FUN_00748a90(param_1,uVar2);
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  FUN_0074b273();
  return;
}

