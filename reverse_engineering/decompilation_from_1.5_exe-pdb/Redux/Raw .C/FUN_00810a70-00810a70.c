
void FUN_00810a70(double *param_1,undefined4 param_2,undefined4 param_3)

{
  double in_XMM0_Qa;
  undefined8 uVar1;
  undefined4 uVar2;
  
  uVar2 = 10;
  uVar1 = __aulldiv(param_2,param_3,10,0);
  __allmul(uVar1,10,0);
  FUN_008448ce(uVar2);
  *param_1 = in_XMM0_Qa;
  __aullrem(param_2,param_3,10,0);
  FUN_008448ce();
  *param_1 = in_XMM0_Qa + *param_1;
  return;
}

