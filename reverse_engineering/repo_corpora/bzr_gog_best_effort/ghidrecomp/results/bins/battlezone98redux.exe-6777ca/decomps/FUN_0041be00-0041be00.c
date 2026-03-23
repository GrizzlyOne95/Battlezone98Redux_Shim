
void __fastcall FUN_0041be00(int *param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(*param_1 + 0x14))();
  if (cVar1 == '\0') {
    if (((param_1[2] == 1) && (param_1[0x29] != 0)) &&
       (cVar1 = (*(code *)param_1[0x29])(), cVar1 == '\0')) {
      param_1[2] = 0;
    }
  }
  else if ((*(char *)((int)param_1 + 0x5d) == '\0') || ((char)param_1[0x2a] != '\0')) {
    if (((char)param_1[0x2a] != '\0') && (*(char *)((int)param_1 + 0x5d) == '\0')) {
      *(undefined1 *)(param_1 + 0x2a) = 0;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x2a) = 1;
    if (param_1[2] == 1) {
      param_1[2] = 0;
    }
    else {
      param_1[2] = 1;
      if (param_1[0x25] != 0) {
        FUN_0041b180();
      }
    }
  }
  if (param_1[2] == 1) {
    if (param_1[0x26] == 0) {
      if (param_1[0x27] != 0) {
        *(undefined1 *)param_1[0x27] = 1;
      }
    }
    else {
      FUN_0061dc10(param_1[0x26]);
    }
  }
  return;
}

