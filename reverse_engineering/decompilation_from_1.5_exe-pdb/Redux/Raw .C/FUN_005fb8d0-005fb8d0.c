
void __fastcall FUN_005fb8d0(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c51c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  pvVar2 = operator_new(0x14c);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x10),1);
  }
  *(undefined4 *)(param_1 + 0x38) = local_20;
  ExceptionList = local_10;
  return;
}

