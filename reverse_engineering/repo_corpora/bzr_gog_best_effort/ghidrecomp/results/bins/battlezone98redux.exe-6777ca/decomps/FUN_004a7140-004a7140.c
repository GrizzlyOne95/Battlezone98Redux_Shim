
char __thiscall FUN_004a7140(int param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  char local_18;
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  for (local_c = 0; local_c < *(int *)(param_1 + 0x188); local_c = local_c + 1) {
    piVar2 = (int *)FUN_004da060(*(undefined4 *)(param_1 + 0x1c + local_c * 4));
    cVar1 = (**(code **)(*piVar2 + 0x38))();
    if (cVar1 != '\0') {
      cVar1 = (**(code **)(*piVar2 + 0x2c))(param_2);
      if ((cVar1 == '\0') || (local_5 == '\0')) {
        local_18 = '\0';
      }
      else {
        local_18 = '\x01';
      }
      local_5 = local_18;
    }
  }
  return local_5;
}

