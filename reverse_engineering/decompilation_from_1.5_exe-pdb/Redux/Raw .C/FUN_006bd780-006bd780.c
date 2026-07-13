
void FUN_006bd780(int param_1)

{
  undefined4 local_8;
  
  local_8 = 0x10;
  while (local_8 = local_8 + -1, -1 < local_8) {
    *(undefined4 *)(param_1 + local_8 * 4) = 0;
  }
  return;
}

