
void __thiscall FUN_0056c690(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0x68) != param_2) {
    *(undefined1 *)(param_1 + 0x6c) = 1;
    iVar1 = FUN_00462630(param_2);
    if (iVar1 != 0) {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 0x7c) = *puVar2;
      *(undefined4 *)(param_1 + 0x80) = puVar2[1];
      *(undefined4 *)(param_1 + 0x84) = puVar2[2];
    }
    *(int *)(param_1 + 0x68) = param_2;
  }
  return;
}

