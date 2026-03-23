
void __thiscall FUN_0056f320(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 100) != param_2) {
    iVar1 = FUN_00462630(param_2);
    if (iVar1 != 0) {
      iVar2 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
      if (*(int *)(iVar2 + 0x14) == 0x50455253) {
        *(undefined1 *)(param_1 + 0x68) = 1;
        puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
        *(undefined4 *)(param_1 + 0x78) = *puVar3;
        *(undefined4 *)(param_1 + 0x7c) = puVar3[1];
        *(undefined4 *)(param_1 + 0x80) = puVar3[2];
        *(int *)(param_1 + 100) = param_2;
      }
    }
  }
  return;
}

