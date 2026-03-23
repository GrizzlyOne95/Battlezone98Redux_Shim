
undefined1 FUN_007c29b0(int param_1,int param_2)

{
  char cVar1;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int local_8;
  
  local_24 = 1.140258e-38;
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && (*(char *)(local_8 + 0x148) != '\0')) {
    local_24 = (float)param_2;
    local_28 = (float)param_1;
    cVar1 = FUN_007d2810();
    if (cVar1 == '\0') {
      if (*(char *)(local_8 + 0x149) != '\0') {
        *(undefined1 *)(local_8 + 0x149) = 0;
        if ((*(uint *)(local_8 + 0x14) & 0x10) == 0) {
          if (*(int *)(local_8 + 0x120) != 0) {
            local_24 = 0.0;
            local_28 = 1.1403194e-38;
            (**(code **)(**(int **)(local_8 + 0x120) + 0x84))();
          }
        }
        else {
          local_1c = (undefined1 *)&local_28;
          local_20 = FUN_004498d0(local_8 + 0x114);
          FUN_007d2b70();
        }
        if (*(int *)(local_8 + 0x150) != 0) {
          local_24 = 0.0;
          local_28 = 1.1403229e-38;
          (**(code **)(local_8 + 0x150))();
        }
      }
    }
    else if (*(char *)(local_8 + 0x149) == '\0') {
      *(undefined1 *)(local_8 + 0x149) = 1;
      if ((*(uint *)(local_8 + 0x14) & 0x20000) == 0) {
        if ((*(uint *)(local_8 + 0x14) & 0x10) == 0) {
          if (*(int *)(local_8 + 0x120) != 0) {
            local_24 = 0.0;
            local_28 = 1.140291e-38;
            (**(code **)(**(int **)(local_8 + 0x120) + 0x84))();
          }
        }
        else {
          local_14 = (undefined1 *)&local_28;
          local_18 = FUN_004498d0(local_8 + 0x114);
          FUN_007d2b70();
        }
      }
      else {
        local_c = (undefined1 *)&local_28;
        local_10 = FUN_004498d0(local_8 + 0x15c);
        FUN_007d2b70();
      }
      if (*(int *)(local_8 + 0x150) != 0) {
        local_24 = 1.4013e-45;
        local_28 = 1.1402944e-38;
        (**(code **)(local_8 + 0x150))();
      }
      if (*(char *)(local_8 + 0x16c) != '\0') {
        local_24 = 0.0;
        local_28 = 0.0;
        FUN_0043aa30(local_8 + 0x16c,0);
        local_24 = 0.0;
        local_28 = 1.1403024e-38;
        FUN_0043a170();
      }
    }
  }
  return *(undefined1 *)(local_8 + 0x149);
}

