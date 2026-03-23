
void __thiscall FUN_00457240(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_2 != (undefined4 *)0x0) {
    puVar2 = param_2;
    puVar3 = (undefined4 *)(param_1 + 0x20);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  FUN_004584c0(param_1);
  FUN_0044de80(param_2,param_3);
  return;
}

