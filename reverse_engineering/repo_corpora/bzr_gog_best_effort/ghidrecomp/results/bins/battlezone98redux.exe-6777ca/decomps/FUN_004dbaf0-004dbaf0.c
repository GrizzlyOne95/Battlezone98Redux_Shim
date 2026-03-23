
void __thiscall FUN_004dbaf0(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0xd4) != 0) {
    FUN_00460600(*(undefined4 *)(param_1 + 0xd4));
  }
  puVar2 = (undefined4 *)(param_1 + 200);
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}

