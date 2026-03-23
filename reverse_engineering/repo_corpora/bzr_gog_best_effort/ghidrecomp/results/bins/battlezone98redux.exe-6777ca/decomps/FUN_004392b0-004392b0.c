
undefined4 FUN_004392b0(int *param_1,char param_2)

{
  undefined4 uVar1;
  int local_24;
  int local_20;
  uint local_1c;
  void *local_18;
  uint local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  local_18 = (void *)0x0;
  local_14 = 0;
  local_10 = 0;
  if (param_1 == (int *)0x0) {
    uVar1 = 0x800401f0;
  }
  else {
    local_8 = FUN_004394a0(param_1,0);
    if (local_8 < 0) {
      uVar1 = 0x80004005;
    }
    else if (*(int *)(local_c + 0xc) == 0) {
      uVar1 = 0;
    }
    else {
      local_8 = (**(code **)(*param_1 + 0x2c))
                          (param_1,0,*(undefined4 *)(local_c + 8),&local_18,&local_14,0,0,0);
      if (local_8 < 0) {
        uVar1 = 0x80004005;
      }
      else {
        FUN_00439830();
        local_8 = FUN_00439930(local_18,local_14,&local_10);
        if (local_8 < 0) {
          uVar1 = 0x80004005;
        }
        else {
          if (local_10 == 0) {
            if (*(short *)(**(int **)(local_c + 0xc) + 0xe) == 8) {
              local_20 = 0x80;
            }
            else {
              local_20 = 0;
            }
            memset(local_18,local_20,local_14);
          }
          else if (local_10 < local_14) {
            if (param_2 == '\0') {
              if (*(short *)(**(int **)(local_c + 0xc) + 0xe) == 8) {
                local_24 = 0x80;
              }
              else {
                local_24 = 0;
              }
              memset((void *)((int)local_18 + local_10),local_24,local_14 - local_10);
            }
            else {
              for (local_1c = local_10; local_1c < local_14; local_1c = local_1c + local_10) {
                local_8 = FUN_00439830();
                if (local_8 < 0) {
                  return 0x80004005;
                }
                local_8 = FUN_00439930((int)local_18 + local_1c,local_14 - local_1c,&local_10);
                if (local_8 < 0) {
                  return 0x80004005;
                }
              }
            }
          }
          (**(code **)(*param_1 + 0x4c))(param_1,local_18,local_14,0,0);
          uVar1 = 0;
        }
      }
    }
  }
  return uVar1;
}

