
void __thiscall FUN_0049c0a0(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  if ((DAT_008eaaa4 == 0) && (iVar2 = FUN_00572a70(), iVar2 == 0)) {
    return;
  }
  if ((((0 < *(int *)(param_1 + 0x16c)) && (DAT_008eaad8 != 9)) && (DAT_008eaad8 != 10)) &&
     ((DAT_008fe240 == 1 && (*(uint *)(param_1 + 0x168) < param_1 + 0x168U)))) {
    puVar1 = *(undefined4 **)(param_1 + 0x168);
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
    puVar1[3] = param_2[3];
    *(undefined4 *)(*(int *)(param_1 + 0x168) + 0x10) = param_3;
    *(int *)(param_1 + 0x168) = *(int *)(param_1 + 0x168) + 0x14;
  }
  return;
}

