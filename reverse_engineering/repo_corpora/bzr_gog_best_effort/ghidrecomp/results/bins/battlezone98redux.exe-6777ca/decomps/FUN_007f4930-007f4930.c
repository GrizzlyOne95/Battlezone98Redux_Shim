
undefined4 FUN_007f4930(undefined8 param_1)

{
  char cVar1;
  float10 fVar2;
  undefined4 local_8;
  
  cVar1 = FUN_007f4fd0(param_1);
  if (cVar1 == '\0') {
    fVar2 = (float10)FUN_007f58b0(param_1);
    if ((100000.0 <= (double)fVar2) || ((double)fVar2 < 0.001)) {
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}

