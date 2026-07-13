
void __fastcall FUN_0059cd60(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 local_28;
  undefined1 local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a4dc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((*(char *)(param_1 + 0x13c) != '\0') && (*(int *)(param_1 + 0x134) != 0)) {
    FUN_00460600(*(undefined4 *)(param_1 + 0x134),local_14);
    *(undefined4 *)(param_1 + 0x134) = 0;
  }
  iVar1 = FUN_0059cc60(local_20);
  if (iVar1 != 0) {
    pvVar2 = operator_new(0x18);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      puVar4 = local_20;
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x150) + 0x18) + 0xc))(puVar4);
      local_28 = FUN_00460490(uVar3,puVar4);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x134) = local_28;
    *(undefined1 *)(param_1 + 0x13c) = 1;
    *(undefined4 *)(param_1 + 8) = 1;
    *(undefined4 *)(param_1 + 0xc) = 1;
    *(undefined4 *)(param_1 + 0x138) = 0;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

