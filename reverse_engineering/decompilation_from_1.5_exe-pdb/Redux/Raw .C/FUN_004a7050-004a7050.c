
void __thiscall FUN_004a7050(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int *piVar2;
  int local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x188); local_8 = local_8 + 1) {
    piVar2 = (int *)FUN_004da060(*(undefined4 *)(param_1 + 0x1c + local_8 * 4));
    cVar1 = (**(code **)(*piVar2 + 0x38))();
    if (cVar1 != '\0') {
      FUN_004dbd60(param_2,param_3);
    }
  }
  return;
}

