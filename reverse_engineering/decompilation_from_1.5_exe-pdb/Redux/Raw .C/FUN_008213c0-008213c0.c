
void FUN_008213c0(int param_1)

{
  if ((*(uint *)(param_1 + 0x5c) & 8) == 0) {
    *(uint *)(param_1 + 0x20) = (*(int *)(param_1 + 0x20) + 1U) % (*(int *)(param_1 + 0x10) + 5U);
    if ((*(int *)(param_1 + 0x20) == *(int *)(param_1 + 0x1c)) &&
       (*(uint *)(param_1 + 0x1c) =
             (*(int *)(param_1 + 0x1c) + 1U) % (*(int *)(param_1 + 0x10) + 5U),
       3 < *(uint *)(param_1 + 0x24))) {
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -4;
    }
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 4;
  }
  else {
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  }
  return;
}

