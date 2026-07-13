
void __thiscall FUN_0045cc40(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  FUN_00461440(param_1,param_2);
  if (*(int *)(param_2 + 0xec) == 0) {
    iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
    if (0 < *(int *)(iVar1 + 0x50)) {
      iVar2 = FUN_00417c70();
      if (param_2 == iVar2) {
        *(undefined4 *)(param_2 + 0xec) = *(undefined4 *)(iVar1 + 0xd4);
      }
      else {
        *(undefined4 *)(param_2 + 0xec) = *(undefined4 *)(iVar1 + 0xd0);
      }
    }
  }
  return;
}

