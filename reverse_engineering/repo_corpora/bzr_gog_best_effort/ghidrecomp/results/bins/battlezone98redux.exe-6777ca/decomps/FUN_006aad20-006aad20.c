
void __fastcall FUN_006aad20(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fec8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  piVar1 = (int *)FUN_006aa210(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  uVar2 = FUN_0041f870();
  (**(code **)(*piVar1 + 0x1c))(uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

