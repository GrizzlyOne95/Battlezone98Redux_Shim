
void __fastcall FUN_005b6d20(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  void *pvVar4;
  float10 fVar5;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c57c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  fVar5 = (float10)(**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 0x1c))
                             (DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if ((float)fVar5 <= 0.5) {
    iVar2 = FUN_00462d50(*(undefined4 *)(param_1 + 0x2c),0x52444550,0xffffffff,0x46afc800);
    if ((iVar2 != 0) && (cVar1 = FUN_004db5b0(iVar2), cVar1 == '\0')) {
      puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 0x50) = *puVar3;
      *(undefined4 *)(param_1 + 0x54) = puVar3[1];
      *(undefined4 *)(param_1 + 0x58) = puVar3[2];
      pvVar4 = operator_new(0x15c);
      local_8 = 0;
      if (pvVar4 == (void *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = FUN_005b89a0(*(undefined4 *)(param_1 + 0x2c),iVar2);
      }
      *(undefined4 *)(param_1 + 0x30) = local_20;
      ExceptionList = local_10;
      return;
    }
    *(undefined4 *)(param_1 + 0x4c) = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0x4c) = 1;
  }
  ExceptionList = local_10;
  return;
}

