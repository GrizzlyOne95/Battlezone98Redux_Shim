
int FUN_00482580(undefined4 param_1,int *param_2,int param_3)

{
  int *piVar1;
  char *local_18;
  uint local_14;
  uint local_10;
  long local_c;
  char *local_8;
  
  local_8 = (char *)FUN_0041f870();
  piVar1 = _errno();
  *piVar1 = 0;
  local_c = strtol(local_8,&local_18,param_3);
  if (local_8 == local_18) {
    std::_Xinvalid_argument("invalid stoi argument");
  }
  piVar1 = _errno();
  if (*piVar1 != 0x22) {
    local_10 = (uint)(local_c < -0x80000000);
    local_14 = (uint)(0x7fffffff < local_c);
    if (local_10 == local_14) {
      if (param_2 != (int *)0x0) {
        *param_2 = (int)local_18 - (int)local_8;
      }
      return local_c;
    }
  }
                    /* WARNING: Subroutine does not return */
  std::_Xout_of_range("stoi argument out of range");
}

