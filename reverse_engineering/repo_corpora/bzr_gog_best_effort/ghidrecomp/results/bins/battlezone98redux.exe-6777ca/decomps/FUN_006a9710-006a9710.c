
bool __fastcall FUN_006a9710(int param_1)

{
  int *piVar1;
  bool bVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fd0b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  bVar2 = *(char *)(param_1 + 0xc) != '\0';
  if (bVar2) {
    local_8 = 0;
    piVar1 = (int *)FUN_006a9180();
    (**(code **)(*piVar1 + 0x2c))();
  }
  ExceptionList = local_10;
  return bVar2;
}

