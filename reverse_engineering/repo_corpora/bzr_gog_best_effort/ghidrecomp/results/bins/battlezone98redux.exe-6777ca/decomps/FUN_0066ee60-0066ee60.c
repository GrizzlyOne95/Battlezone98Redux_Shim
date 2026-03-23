
undefined1 __thiscall FUN_0066ee60(undefined4 param_1,int *param_2,int *param_3)

{
  char cVar1;
  undefined1 uVar2;
  
  if (*param_2 < *param_3) {
LAB_0066eea2:
    uVar2 = 1;
  }
  else {
    if (*param_2 <= *param_3) {
      cVar1 = FUN_004269f0(param_2 + 1,param_3 + 1,param_1);
      if (cVar1 != '\0') goto LAB_0066eea2;
    }
    uVar2 = 0;
  }
  return uVar2;
}

