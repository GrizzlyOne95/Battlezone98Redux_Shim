
int FUN_008186c0(char param_1)

{
  int iVar1;
  
  if ((param_1 < '0') || ('9' < param_1)) {
    iVar1 = FUN_007fb000((int)param_1);
    iVar1 = iVar1 + -0x57;
  }
  else {
    iVar1 = param_1 + -0x30;
  }
  return iVar1;
}

