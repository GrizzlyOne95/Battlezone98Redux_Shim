
undefined4 FUN_007c2d00(int param_1,int param_2,int param_3)

{
  char cVar1;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int local_8;
  
  local_14 = 1.1403768e-38;
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && (*(char *)(local_8 + 0x148) != '\0')) {
    local_14 = (float)param_2;
    local_18 = (float)param_1;
    cVar1 = FUN_007d2810();
    if ((cVar1 != '\0') &&
       (((param_3 == 0 && (*(char *)(local_8 + 0x14a) != '\0')) ||
        ((param_3 == 1 && ((*(char *)(local_8 + 0x14b) != '\0' && (*(int *)(local_8 + 0x158) != 0)))
         ))))) {
      if (((*(uint *)(local_8 + 0x14) & 0x20000) == 0) || ((*(uint *)(local_8 + 0x14) & 0x10) == 0))
      {
        if (*(int *)(local_8 + 0x120) != 0) {
          local_14 = 0.0;
          local_18 = 1.1404103e-38;
          (**(code **)(**(int **)(local_8 + 0x120) + 0x84))();
        }
      }
      else {
        local_c = (undefined1 *)&local_18;
        local_10 = FUN_004498d0(local_8 + 0x15c);
        FUN_007d2b70();
      }
      if (param_3 == 0) {
        *(undefined1 *)(local_8 + 0x14a) = 0;
        if (*(int *)(local_8 + 0x154) != 0) {
          local_14 = 1.1404158e-38;
          (**(code **)(local_8 + 0x154))();
        }
      }
      else if ((param_3 == 1) &&
              (*(undefined1 *)(local_8 + 0x14b) = 0, *(int *)(local_8 + 0x158) != 0)) {
        local_14 = 1.1404215e-38;
        (**(code **)(local_8 + 0x158))();
      }
      return 1;
    }
  }
  return 0;
}

