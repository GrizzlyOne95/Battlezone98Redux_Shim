
undefined8 FUN_004622a0(float param_1,float param_2)

{
  float10 fVar1;
  double dVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  dVar2 = (double)(param_1 * param_1 + param_2 * param_2);
  if (dVar2 <= 0.0) {
    local_8 = 0.0;
    local_c = 0.0;
  }
  else {
    fVar1 = (float10)FUN_00820570(dVar2);
    local_c = param_1 * (float)fVar1;
    local_8 = param_2 * (float)fVar1;
  }
  return CONCAT44(local_8,local_c);
}

