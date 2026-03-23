
undefined4 FUN_0043d6c0(int *param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  uint local_c;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    uVar1 = 0x800401f0;
  }
  else {
    if (param_2 != (undefined1 *)0x0) {
      *param_2 = 0;
    }
    local_8 = (**(code **)(*param_1 + 0x24))(param_1,&local_c);
    if (local_8 < 0) {
      uVar1 = 0x80004005;
    }
    else if ((local_c & 2) == 0) {
      uVar1 = 1;
    }
    else {
      do {
        local_8 = (**(code **)(*param_1 + 0x50))(param_1);
        if (local_8 == -0x7787ff6a) {
          Sleep(10);
        }
        local_8 = (**(code **)(*param_1 + 0x50))(param_1);
      } while (local_8 != 0);
      if (param_2 != (undefined1 *)0x0) {
        *param_2 = 1;
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}

