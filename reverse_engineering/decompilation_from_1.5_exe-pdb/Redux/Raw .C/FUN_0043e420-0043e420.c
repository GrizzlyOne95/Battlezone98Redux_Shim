
void __fastcall FUN_0043e420(int param_1)

{
  void *local_14;
  size_t local_10;
  int local_c;
  int local_8;
  
  local_14 = (void *)0x0;
  local_10 = 0;
  local_8 = param_1;
  local_c = FUN_0043d6c0(*(undefined4 *)(param_1 + 0x60),0);
  if ((-1 < local_c) &&
     (local_c = (**(code **)(**(int **)(local_8 + 0x60) + 0x2c))
                          (*(undefined4 *)(local_8 + 0x60),0,*(undefined4 *)(local_8 + 0x4c),
                           &local_14,&local_10,0,0,0), -1 < local_c)) {
    memset(local_14,0,local_10);
    (**(code **)(**(int **)(local_8 + 0x60) + 0x4c))
              (*(undefined4 *)(local_8 + 0x60),local_14,local_10,0,0);
  }
  return;
}

