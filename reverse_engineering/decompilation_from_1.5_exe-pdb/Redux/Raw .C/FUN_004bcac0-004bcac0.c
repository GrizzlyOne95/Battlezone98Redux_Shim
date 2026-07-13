
undefined1 FUN_004bcac0(ushort *param_1,ushort *param_2)

{
  undefined1 local_8;
  
  if ((*param_1 < *param_2) ||
     ((*param_1 <= *param_2 && (*(uint *)(param_1 + 2) < *(uint *)(param_2 + 2))))) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}

