
undefined1 FUN_00585c70(ushort *param_1,ushort *param_2)

{
  undefined1 local_8;
  
  if ((*param_1 < *param_2) || ((*param_1 <= *param_2 && (param_1[1] < param_2[1])))) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}

