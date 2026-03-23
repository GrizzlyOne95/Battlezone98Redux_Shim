
void __thiscall FUN_004a7300(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  
  *param_2 = param_3;
  iVar1 = FUN_00477590(param_4,param_1);
  param_2[1] = iVar1;
  if (param_3 == 0) {
    param_2[3] = DAT_00917588;
  }
  else if (param_4 == 0) {
    if (param_3 == 3) {
      param_2[3] = DAT_009175b0;
    }
    else {
      param_2[3] = DAT_0091755c;
    }
  }
  else {
    iVar1 = FUN_00492ce0();
    param_2[3] = iVar1;
  }
  return;
}

