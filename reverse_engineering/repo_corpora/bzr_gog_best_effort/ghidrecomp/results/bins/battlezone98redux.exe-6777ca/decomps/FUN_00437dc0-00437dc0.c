
undefined4 FUN_00437dc0(undefined4 param_1)

{
  undefined4 *local_18;
  undefined4 *local_c;
  int local_8;
  
  local_18 = operator_new(8);
  if (local_18 == (undefined4 *)0x0) {
    local_18 = (undefined4 *)0x0;
  }
  else {
    memset(local_18,0,8);
  }
  local_c = local_18;
  *local_18 = param_1;
  local_18[1] = *(undefined4 *)(local_8 + 0x30);
  *(int *)(local_8 + 0x30) = *(int *)(local_8 + 0x30) + 1;
  FUN_00438be0(&local_c);
  return local_c[1];
}

