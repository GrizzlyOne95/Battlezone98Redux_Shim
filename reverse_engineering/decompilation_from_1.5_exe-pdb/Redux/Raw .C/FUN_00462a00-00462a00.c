
float10 FUN_00462a00(float param_1)

{
  undefined4 local_8;
  
  if (3.0 <= param_1) {
    if (5.0 <= param_1) {
      if (15.0 <= param_1) {
        local_8 = 1.0;
      }
      else {
        local_8 = 2.0;
      }
    }
    else {
      local_8 = 3.0;
    }
  }
  else {
    local_8 = 100.0;
  }
  return (float10)local_8;
}

