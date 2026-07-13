
void FUN_006dcea0(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  while( true ) {
    if (param_3 == 0) break;
    param_3 = param_3 + -1;
    uVar1 = FUN_006ef1a0(&param_2);
    FUN_006ef1c0(param_1,uVar1);
    param_2 = param_2 + 0x20;
  }
  return;
}

