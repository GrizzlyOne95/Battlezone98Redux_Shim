
void __fastcall FUN_005b69e0(int param_1)

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
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x40),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x4c) = 1;
  }
  else {
    pvVar2 = operator_new(0x15c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_005b83e0(*(undefined4 *)(param_1 + 0x2c),iVar1);
    }
    *(undefined4 *)(param_1 + 0x30) = local_20;
  }
  ExceptionList = local_10;
  return;
}

