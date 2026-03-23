
void __thiscall FUN_004c8800(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((DAT_008eaaa4 == 0) && (iVar1 = FUN_00572a70(), iVar1 == 0)) {
    return;
  }
  if ((((DAT_008eaad8 != 9) && (DAT_008eaad8 != 10)) && (DAT_008fe240 == 1)) &&
     (*(uint *)(param_1 + 0x1228) < param_1 + 0x1228U)) {
    puVar2 = *(undefined4 **)(param_1 + 0x1228);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_2;
      param_2 = param_2 + 1;
      puVar2 = puVar2 + 1;
    }
    *(undefined4 *)(*(int *)(param_1 + 0x1228) + 0x40) = param_3;
    *(int *)(param_1 + 0x1228) = *(int *)(param_1 + 0x1228) + 0x48;
  }
  return;
}

