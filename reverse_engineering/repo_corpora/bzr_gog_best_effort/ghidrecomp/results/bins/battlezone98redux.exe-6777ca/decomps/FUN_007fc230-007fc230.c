
float10 FUN_007fc230(double param_1)

{
  undefined4 local_c;
  uint local_8;
  
  FUN_007d72b0(param_1,&local_c);
  local_8 = local_8 ^ 0x80000000;
  FUN_007fb030(&param_1,local_c,local_8);
  return (float10)param_1;
}

