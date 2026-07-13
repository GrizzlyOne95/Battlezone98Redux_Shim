
void __thiscall FUN_007cfd40(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  
  if (DAT_009456c8 != (code *)0x0) {
    cVar1 = FUN_007d3360();
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x92c) != '\0')) {
      cVar1 = FUN_007d2810((float)param_2,(float)param_3);
      if (cVar1 != '\0') {
        (*DAT_009456c8)(param_1,1);
      }
    }
  }
  FUN_007cc940(param_2,param_3,param_4);
  return;
}

