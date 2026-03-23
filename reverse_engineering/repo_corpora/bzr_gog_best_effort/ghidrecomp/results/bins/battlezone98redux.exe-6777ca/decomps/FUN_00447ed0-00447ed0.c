
float10 FUN_00447ed0(float param_1,float param_2,float param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_2 <= param_1) {
    if (param_1 <= param_3) {
      local_8 = param_1;
    }
    else {
      local_8 = param_3;
    }
    local_c = local_8;
  }
  else {
    local_c = param_2;
  }
  return (float10)local_c;
}

