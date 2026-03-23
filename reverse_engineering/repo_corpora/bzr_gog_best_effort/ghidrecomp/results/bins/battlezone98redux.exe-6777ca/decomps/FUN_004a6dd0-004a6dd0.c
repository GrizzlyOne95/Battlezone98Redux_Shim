
void __thiscall FUN_004a6dd0(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int local_c;
  
  for (local_c = 0; local_c < *(int *)(param_1 + 0x188); local_c = local_c + 1) {
    FUN_004da060(*(undefined4 *)(param_1 + 0x1c + local_c * 4));
    FUN_0049f3c0(0);
  }
  *(undefined4 *)(param_1 + 0x188) = 0;
  for (local_c = 0; local_c < *(int *)(param_1 + 0xfc4 + param_2 * 4); local_c = local_c + 1) {
    piVar2 = (int *)FUN_004da060(*(undefined4 *)(param_1 + 0x18c + param_2 * 0x16c + local_c * 4));
    if (piVar2 != (int *)0x0) {
      cVar1 = (**(code **)(*piVar2 + 0x38))();
      if (cVar1 != '\0') {
        *(undefined4 *)(param_1 + 0x1c + *(int *)(param_1 + 0x188) * 4) =
             *(undefined4 *)(param_1 + 0x18c + param_2 * 0x16c + local_c * 4);
        *(int *)(param_1 + 0x188) = *(int *)(param_1 + 0x188) + 1;
        FUN_0049f3c0(1);
      }
    }
  }
  *(undefined4 *)(param_1 + 0x117c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1188) = 0;
  return;
}

