
void FUN_004350e0(int *param_1)

{
  int iVar1;
  int local_c;
  int local_8;
  
  iVar1 = FUN_004344a0();
  if (iVar1 != 2) {
    local_c = *param_1;
    local_8 = param_1[1];
    iVar1 = FUN_00434fd0(&local_c);
    if (iVar1 != 0) {
      SetCursorPos(local_c,local_8);
    }
  }
  return;
}

