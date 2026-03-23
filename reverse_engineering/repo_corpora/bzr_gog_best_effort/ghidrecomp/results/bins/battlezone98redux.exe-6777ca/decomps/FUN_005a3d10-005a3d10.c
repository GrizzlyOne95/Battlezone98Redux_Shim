
void __fastcall FUN_005a3d10(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(char *)(param_1 + 0x7c) != '\0') {
    *(undefined1 *)(param_1 + 0x7c) = 0;
    iVar1 = FUN_00473940();
    if (iVar1 != 0) {
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 4))();
      FUN_005a38a0(uVar2);
    }
  }
  if (*(undefined4 **)(param_1 + 0x38) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x38))(1);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  return;
}

