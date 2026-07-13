
float10 FUN_007d7300(double param_1)

{
  char cVar1;
  double local_c;
  
  cVar1 = FUN_007d9720(param_1);
  if (cVar1 == '\0') {
    local_c = param_1;
  }
  else {
    local_c = -param_1;
  }
  return (float10)local_c;
}

