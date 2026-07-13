
void FUN_00680620(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0xd0);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x140))(*(undefined4 *)(param_1 + 0x14));
    FUN_0067e550(piVar1);
  }
  return;
}

