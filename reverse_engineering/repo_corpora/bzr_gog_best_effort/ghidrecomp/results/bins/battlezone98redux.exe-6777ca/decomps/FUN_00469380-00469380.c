
void FUN_00469380(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = FUN_00468980(param_2,param_3);
  if (cVar1 == '\0') {
    *(byte *)(DAT_0260d178 + param_1) = *(byte *)(DAT_0260d178 + param_1) & 0xf7;
  }
  return;
}

