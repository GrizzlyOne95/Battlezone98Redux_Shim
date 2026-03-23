
int FUN_00453d10(int param_1,int param_2,int param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_1 < param_2) {
    local_c = param_2;
  }
  else {
    if (param_3 < param_1) {
      local_8 = param_3;
    }
    else {
      local_8 = param_1;
    }
    local_c = local_8;
  }
  return local_c;
}

