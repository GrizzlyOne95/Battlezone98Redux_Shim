
void FUN_00693290(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 4) == 1) {
    for (local_8 = 0; local_8 < *(int *)(param_1 + 8); local_8 = local_8 + 1) {
      *(undefined4 *)(*(int *)(param_1 + 0xc) + 8 + local_8 * 0xc) =
           *(undefined4 *)(*(int *)(param_1 + 0xc) + 4 + local_8 * 0xc);
    }
  }
  else if (*(int *)(param_1 + 4) == 2) {
    for (local_8 = 0; local_8 < *(int *)(param_1 + 8); local_8 = local_8 + 1) {
      *(undefined4 *)(*(int *)(param_1 + 0xc) + 8 + local_8 * 0xc) = 0;
    }
  }
  return;
}

