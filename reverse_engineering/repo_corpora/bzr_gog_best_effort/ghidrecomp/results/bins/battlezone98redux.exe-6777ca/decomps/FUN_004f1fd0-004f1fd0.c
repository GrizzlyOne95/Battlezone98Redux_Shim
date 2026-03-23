
void __fastcall FUN_004f1fd0(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  float10 fVar4;
  undefined1 *puVar5;
  undefined4 local_2c;
  int local_28;
  undefined1 local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a5fc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x164) < 5) {
    fVar4 = (float10)FUN_00822d80(local_14);
    *(float *)(param_1 + 0x150 + *(int *)(param_1 + 0x164) * 4) = (float)fVar4;
    *(int *)(param_1 + 0x164) = *(int *)(param_1 + 0x164) + 1;
  }
  else {
    for (local_28 = 1; local_28 < 6; local_28 = local_28 + 1) {
      *(undefined4 *)(param_1 + 0x14c + local_28 * 4) =
           *(undefined4 *)(param_1 + 0x150 + local_28 * 4);
    }
    fVar4 = (float10)FUN_00822d80(local_14);
    *(float *)(param_1 + 0x160) = (float)fVar4;
  }
  if ((*(char *)(param_1 + 0x13c) != '\0') && (*(int *)(param_1 + 0x134) != 0)) {
    FUN_00460600(*(undefined4 *)(param_1 + 0x134));
    *(undefined4 *)(param_1 + 0x134) = 0;
  }
  iVar1 = FUN_004f1a40(local_20);
  if (iVar1 != 0) {
    pvVar2 = operator_new(0x18);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_2c = 0;
    }
    else {
      puVar5 = local_20;
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x14c) + 0x18) + 0xc))(puVar5);
      local_2c = FUN_00460490(uVar3,puVar5);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x134) = local_2c;
    *(undefined1 *)(param_1 + 0x13c) = 1;
    *(undefined4 *)(param_1 + 8) = 1;
    *(undefined4 *)(param_1 + 0xc) = 1;
    *(undefined4 *)(param_1 + 0x138) = 0;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

