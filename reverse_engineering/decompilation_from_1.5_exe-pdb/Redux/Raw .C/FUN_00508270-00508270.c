
undefined4 FUN_00508270(undefined4 param_1)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 local_10;
  
  pfVar1 = (float *)FUN_004ff7c0(param_1,1);
  pfVar2 = (float *)FUN_004ff7c0(param_1,2);
  if (((*pfVar1 == *pfVar2) && (pfVar1[1] == pfVar2[1])) && (pfVar1[2] == pfVar2[2])) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  FUN_0082cbf5(param_1,local_10);
  return 1;
}

