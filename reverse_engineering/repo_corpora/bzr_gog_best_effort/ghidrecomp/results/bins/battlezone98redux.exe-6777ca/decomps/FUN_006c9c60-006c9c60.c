
undefined1 __thiscall FUN_006c9c60(int param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int in_stack_ffffffe4;
  
  if ((*(int *)(param_3 + 0x10) == 0) && (param_3 != *(int *)(param_1 + 8))) {
    cVar1 = FUN_006dc8e0(param_2);
    if (cVar1 == '\0') {
      uVar3 = FUN_0046b240();
      *(undefined4 *)(param_3 + 8) = uVar3;
      FUN_006ceb10(&stack0xffffffe4);
      iVar2 = FUN_0046b240();
      FUN_006ce960(iVar2 + -1);
    }
    else {
      iVar2 = eof(in_stack_ffffffe4);
      *(int *)(param_3 + 8) = iVar2;
    }
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_3 + 0x10) = 0;
    if (*(int *)(param_1 + 8) != 0) {
      *(int *)(*(int *)(param_1 + 8) + 0x10) = param_3;
    }
    *(int *)(param_1 + 8) = param_3;
  }
  FUN_006c9000(param_4);
  if ((*(int *)(param_3 + 8) == 0) && (iVar2 = get(), iVar2 == param_4)) {
    return 1;
  }
  return 0;
}

