
void FUN_00432450(int *param_1)

{
  undefined4 local_8;
  
  if ((*(char *)*param_1 == '\r') && (*(char *)(*param_1 + 1) == '\n')) {
    local_8 = 2;
  }
  else {
    local_8 = 1;
  }
  *param_1 = *param_1 + local_8;
  return;
}

