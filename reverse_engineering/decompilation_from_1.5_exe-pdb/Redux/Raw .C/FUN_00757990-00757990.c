
void FUN_00757990(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  int local_8;
  
  while (local_8 = (param_2 + -1) / 2, param_3 < param_2) {
    cVar1 = FUN_00754c60(local_8 * 0x50 + param_1,param_4);
    if (cVar1 == '\0') break;
    uVar2 = FUN_00417780(local_8 * 0x50 + param_1);
    FUN_007575c0(uVar2);
    param_2 = local_8;
  }
  uVar2 = FUN_00417780(param_4);
  FUN_007575c0(uVar2);
  return;
}

