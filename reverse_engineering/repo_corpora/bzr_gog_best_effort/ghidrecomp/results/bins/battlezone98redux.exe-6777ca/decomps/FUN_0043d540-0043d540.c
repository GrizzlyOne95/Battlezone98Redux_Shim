
undefined4 FUN_0043d540(void *param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)((int)param_1 + 0x20);
  if (*(int *)((int)param_1 + 0x14) != 0) {
    FUN_0043aaa0(*(undefined4 *)((int)param_1 + 0x14));
  }
  free(param_1);
  return uVar1;
}

