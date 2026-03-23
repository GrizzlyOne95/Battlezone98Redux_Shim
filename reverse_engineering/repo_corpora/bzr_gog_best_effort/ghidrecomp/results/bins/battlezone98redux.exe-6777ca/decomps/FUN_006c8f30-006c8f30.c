
void __fastcall FUN_006c8f30(int *param_1)

{
  int iVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008526f8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  while (iVar1 = *param_1, iVar1 != 0) {
    FUN_006c8fb0();
    FUN_006dc6e0(iVar1);
  }
  local_8 = 0xffffffff;
  FUN_00417c60(uVar2);
  ExceptionList = local_10;
  return;
}

