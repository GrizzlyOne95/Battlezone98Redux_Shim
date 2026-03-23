
void FUN_0043bc60(void)

{
  int *piVar1;
  int *piVar2;
  int *local_10;
  int *local_8;
  
  piVar2 = DAT_00915598;
  if (*DAT_00915598 != 0) {
    piVar1 = (int *)*DAT_00915598;
    local_10 = (int *)0x0;
    for (local_8 = piVar1; local_8 != (int *)0x0; local_8 = (int *)*local_8) {
      if (local_8[0xd] < DAT_00915598[0xd]) {
        *DAT_00915598 = (int)local_8;
        DAT_00915598 = piVar1;
        if (local_10 == (int *)0x0) {
          DAT_00915598 = piVar2;
          return;
        }
        *local_10 = (int)piVar2;
        return;
      }
      if (DAT_00915598[0xd] == local_8[0xd]) {
        *DAT_00915598 = *local_8;
        DAT_00915598 = piVar1;
        *local_8 = (int)piVar2;
        return;
      }
      local_10 = local_8;
    }
    *DAT_00915598 = 0;
    DAT_00915598 = piVar1;
    *local_10 = (int)piVar2;
  }
  return;
}

