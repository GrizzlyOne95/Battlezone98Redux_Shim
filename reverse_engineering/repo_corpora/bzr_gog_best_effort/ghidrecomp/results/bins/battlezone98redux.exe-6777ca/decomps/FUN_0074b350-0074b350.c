
long FUN_0074b350(undefined4 param_1,int *param_2,int param_3)

{
  int *piVar1;
  long lVar2;
  char *local_c;
  char *local_8;
  
  local_8 = (char *)FUN_0041f870();
  piVar1 = _errno();
  *piVar1 = 0;
  lVar2 = strtol(local_8,&local_c,param_3);
  if (local_8 == local_c) {
    std::_Xinvalid_argument("invalid stol argument");
  }
  piVar1 = _errno();
  if (*piVar1 == 0x22) {
                    /* WARNING: Subroutine does not return */
    std::_Xout_of_range("stol argument out of range");
  }
  if (param_2 != (int *)0x0) {
    *param_2 = (int)local_c - (int)local_8;
  }
  return lVar2;
}

