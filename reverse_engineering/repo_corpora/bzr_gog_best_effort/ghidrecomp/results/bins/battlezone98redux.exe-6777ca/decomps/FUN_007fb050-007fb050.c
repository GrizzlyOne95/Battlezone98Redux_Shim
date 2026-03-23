
float10 FUN_007fb050(char param_1,double param_2)

{
  float10 fVar1;
  undefined8 local_c;
  
  if (param_1 == '\0') {
    local_c = param_2;
  }
  else {
    fVar1 = (float10)FUN_007fc230(param_2);
    local_c = (double)fVar1;
  }
  return (float10)local_c;
}

