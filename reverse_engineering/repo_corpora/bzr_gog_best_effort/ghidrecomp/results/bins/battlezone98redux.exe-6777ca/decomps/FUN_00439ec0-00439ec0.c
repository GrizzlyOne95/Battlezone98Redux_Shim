
bool FUN_00439ec0(int param_1)

{
  bool bVar1;
  uint local_c [2];
  
  if (*(int *)(param_1 + 0x7c) == 0) {
    bVar1 = false;
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x7c) + 0x24))(*(undefined4 *)(param_1 + 0x7c),local_c);
    bVar1 = (local_c[0] & 1) != 0;
  }
  return bVar1;
}

