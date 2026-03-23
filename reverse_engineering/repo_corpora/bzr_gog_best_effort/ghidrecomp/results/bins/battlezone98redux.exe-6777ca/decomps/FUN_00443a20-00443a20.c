
void FUN_00443a20(int param_1)

{
  int iVar1;
  
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
    iVar1 = FUN_0043fff0(param_1);
    if (iVar1 == 0x3000) {
      FUN_00444540(param_1);
    }
    if (*(int *)(param_1 + 0x80) != 0) {
      FUN_00443a20(*(undefined4 *)(param_1 + 0x80));
    }
  }
  return;
}

