
void FUN_004697c0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  *(byte *)(DAT_0260d178 + param_1) = *(byte *)(DAT_0260d178 + param_1) & 0xf4;
  cVar1 = FUN_00468890(param_2,param_3);
  if (cVar1 == '\0') {
    cVar1 = FUN_00468450(param_2,param_3);
    if (cVar1 != '\0') {
      *(byte *)(DAT_0260d178 + param_1) = *(byte *)(DAT_0260d178 + param_1) | 1;
    }
  }
  else {
    *(byte *)(DAT_0260d178 + param_1) = *(byte *)(DAT_0260d178 + param_1) | 2;
  }
  return;
}

