
void __fastcall FUN_005d9840(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xcc) != 0) {
    iVar1 = FUN_00417c70();
    if (*(int *)(param_1 + 0xcc) == iVar1) {
      iVar1 = FUN_005d9640();
      if (iVar1 == 0) {
        *(undefined1 *)(param_1 + 0xc0) = 0;
      }
    }
  }
  return;
}

