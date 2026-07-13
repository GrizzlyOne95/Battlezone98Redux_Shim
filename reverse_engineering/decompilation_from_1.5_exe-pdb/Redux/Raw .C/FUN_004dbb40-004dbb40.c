
undefined4 __fastcall FUN_004dbb40(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (*(int *)(param_1 + 0xcc) == 1) {
    *(undefined4 *)(param_1 + 0xcc) = 0;
    uVar1 = 1;
  }
  else {
    if (*(int *)(param_1 + 0xb4) != 0) {
      FUN_00460600(*(undefined4 *)(param_1 + 0xb4));
    }
    puVar3 = (undefined4 *)(param_1 + 200);
    puVar4 = (undefined4 *)(param_1 + 0xa8);
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(param_1 + 200) = 0;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined4 *)(param_1 + 0xd0) = 0;
    *(undefined4 *)(param_1 + 0xd4) = 0;
    *(undefined4 *)(param_1 + 0xe0) = 0;
    *(undefined4 *)(param_1 + 0xe4) = 0;
    uVar1 = *(undefined4 *)(param_1 + 0xac);
  }
  return uVar1;
}

