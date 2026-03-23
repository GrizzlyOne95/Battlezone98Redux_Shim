
void __thiscall FUN_00496550(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849400;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_004966a0(param_2);
  if (cVar1 != '\0') {
    local_8 = 0;
    uVar2 = FUN_00496760(*param_1,param_2,param_3);
    param_1[1] = uVar2;
    FUN_004965d4();
    return;
  }
  ExceptionList = local_10;
  return;
}

