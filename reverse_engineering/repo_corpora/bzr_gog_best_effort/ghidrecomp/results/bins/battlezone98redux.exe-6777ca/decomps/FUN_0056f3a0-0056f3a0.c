
void __fastcall FUN_0056f3a0(int param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  undefined4 local_30;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b5dc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0050aa10(local_14);
  cVar1 = FUN_0049a000();
  if (cVar1 != '\0') {
    uVar2 = FUN_00822d90();
    uVar2 = uVar2 / 1000;
    if (uVar2 + 2 < *(uint *)(param_1 + 0x84)) {
      *(uint *)(param_1 + 0x84) = uVar2 - 1;
    }
    if (*(uint *)(param_1 + 0x84) < uVar2) {
      FUN_004ff080(uVar2,0x7fffffff,0x7fffffff);
      *(uint *)(param_1 + 0x84) = uVar2;
    }
  }
  if ((*(char *)(param_1 + 0x69) == '\0') && (*(char *)(param_1 + 0x68) != '\0')) {
    *(undefined1 *)(param_1 + 0x68) = 0;
    local_20 = *(float *)(param_1 + 0x78) + 10.0;
    local_1c = *(float *)(param_1 + 0x7c) + 10.0;
    local_18 = *(float *)(param_1 + 0x80) + 10.0;
    *(undefined4 *)(param_1 + 0x70) = 10;
    *(undefined4 *)(param_1 + 0x74) = 10;
    pvVar3 = operator_new(0x18);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = FUN_00460490(&local_20,param_1 + 0x78);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x6c) = local_30;
    FUN_005cd2a0();
    *(undefined1 *)(param_1 + 0x69) = 1;
    iVar4 = FUN_00822e60();
    DAT_00917f3c = iVar4 + 2000;
  }
  if (*(char *)(param_1 + 0x69) != '\0') {
    FUN_00822560(*(undefined4 *)(param_1 + 0x6c),param_1 + 0x70,param_1 + 0x74);
    cVar1 = FUN_005cd560();
    if ((cVar1 != '\0') || (uVar2 = FUN_00822e60(), DAT_00917f3c < uVar2)) {
      FUN_005cd4e0();
      if (*(int *)(param_1 + 0x6c) != 0) {
        FUN_00460640(1);
      }
      *(undefined1 *)(param_1 + 0x69) = 0;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

