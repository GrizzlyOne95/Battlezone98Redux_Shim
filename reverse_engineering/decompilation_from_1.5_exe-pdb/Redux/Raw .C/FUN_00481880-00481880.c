
void FUN_00481880(int *param_1,void *param_2)

{
  int iVar1;
  int *local_c;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    local_c = &DAT_0091739c;
  }
  else {
    local_c = param_1;
  }
  if (param_2 != (void *)0x0) {
    *(undefined2 *)((int)param_2 + 0x14) = 0;
    FUN_00481550(local_c,param_2);
    iVar1 = FUN_00481440(param_2);
    if (param_2 == *(void **)(*local_c + iVar1 * 4)) {
      *(undefined4 *)(*local_c + iVar1 * 4) = *(undefined4 *)((int)param_2 + 0x1c);
    }
    else {
      for (local_8 = *(int *)(*local_c + iVar1 * 4);
          ((local_8 != 0 && (*(int *)(local_8 + 0x1c) != 0)) &&
          (*(void **)(local_8 + 0x1c) != param_2)); local_8 = *(int *)(local_8 + 0x1c)) {
      }
      if ((local_8 == 0) || (*(int *)(local_8 + 0x1c) == 0)) {
        if (param_2 != (void *)local_c[3]) {
          return;
        }
        FUN_004815e0(local_c);
        return;
      }
      *(undefined4 *)(local_8 + 0x1c) = *(undefined4 *)(*(int *)(local_8 + 0x1c) + 0x1c);
    }
    free(param_2);
    local_c[1] = local_c[1] + -1;
  }
  return;
}

