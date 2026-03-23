
void __fastcall FUN_0041bb60(int *param_1)

{
  char cVar1;
  char *local_10;
  
  cVar1 = (**(code **)(*param_1 + 0x14))();
  if (cVar1 == '\0') {
    *(undefined1 *)((int)param_1 + 0x5d) = 0;
  }
  if (*(char *)((int)param_1 + 0x5d) == '\0') {
    param_1[2] = 0;
  }
  else if ((param_1[2] != 1) || ((char)param_1[0xf] != '\0')) {
    param_1[2] = 1;
    if (param_1[0x26] == 0) {
      if (param_1[0x27] == 0) {
        if (param_1[0x28] != 0) {
          local_10 = (char *)param_1[0x28];
          FUN_0061d2d0(0x300);
          if (local_10 != (char *)0x0) {
            for (; *local_10 != '\0'; local_10 = local_10 + 1) {
              FUN_0061d2d0((short)*local_10 | 0x300);
            }
          }
        }
      }
      else {
        *(undefined1 *)param_1[0x27] = 1;
        if (param_1[0x25] != 0) {
          FUN_0041b180();
        }
      }
    }
    else {
      FUN_0061dc10(param_1[0x26]);
      if (param_1[0x25] != 0) {
        FUN_0041b180();
      }
    }
  }
  return;
}

