
float10 FUN_006948f0(undefined4 param_1)

{
  int local_10;
  int local_c;
  float local_8;
  
  local_8 = 0.0;
  FUN_00694830(param_1,&local_10,&local_c);
  if (local_c < 1) {
    local_8 = (float)local_10;
  }
  else {
    local_8 = (float)local_10 / (float)local_c;
  }
  return (float10)local_8;
}

