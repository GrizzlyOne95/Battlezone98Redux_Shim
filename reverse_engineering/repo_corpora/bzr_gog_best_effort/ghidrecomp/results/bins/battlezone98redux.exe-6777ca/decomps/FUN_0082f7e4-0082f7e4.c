
void FUN_0082f7e4(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 6) == '\0') {
    iVar1 = FUN_0082f2d3(param_1,param_2 + -0x10,0xffffffff);
    if (iVar1 != 0) {
      return;
    }
  }
  else {
    *(undefined1 *)(param_1 + 6) = 0;
    if (*(char *)(*(int *)(*(undefined4 **)(param_1 + 0x14))[1] + 6) == '\0') {
      *(undefined4 *)(param_1 + 0xc) = **(undefined4 **)(param_1 + 0x14);
    }
    else {
      iVar1 = FUN_0082f246(param_1,param_2);
      if (iVar1 != 0) {
        *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 8);
      }
    }
  }
  FUN_00832183(param_1,(*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x28)) / 0x18);
  return;
}

