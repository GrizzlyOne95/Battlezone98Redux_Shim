
void FUN_00840890(short *param_1,undefined4 param_2)

{
  short sVar1;
  short *psVar2;
  
  if (*param_1 == 0) {
    FUN_008408e0(param_1,param_2,0);
    return;
  }
  psVar2 = param_1;
  do {
    sVar1 = *psVar2;
    psVar2 = psVar2 + 1;
  } while (sVar1 != 0);
  FUN_008408e0(param_1,param_2,(int)psVar2 - (int)(param_1 + 1) >> 1);
  return;
}

