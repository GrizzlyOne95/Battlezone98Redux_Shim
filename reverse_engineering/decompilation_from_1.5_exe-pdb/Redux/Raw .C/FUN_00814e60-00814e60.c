
void __thiscall FUN_00814e60(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 local_4c [56];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864d28;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00815090(local_14);
  local_8 = 0;
  uVar1 = *(undefined4 *)*param_1;
  cVar2 = FUN_00815140(param_2,local_4c);
  if ((cVar2 == '\0') && (cVar2 = FUN_00815190(param_1[4],local_4c), cVar2 == '\0')) {
    *(undefined4 *)*param_1 = uVar1;
  }
  local_8 = 0xffffffff;
  FUN_0071b820();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

