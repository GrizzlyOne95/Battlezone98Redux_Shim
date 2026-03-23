
undefined4 __thiscall FUN_00702ca0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_34 [28];
  undefined4 local_18;
  undefined1 *local_14;
  int local_10;
  undefined4 local_c;
  undefined **local_8;
  
  local_c = 0;
  if (*(char *)(param_1 + 4) == '\0') {
    local_8 = (undefined **)&DAT_00896cb4;
  }
  else {
    local_8 = &PTR_LAB_00896ca8;
  }
  local_14 = auStack_34;
  local_10 = param_1;
  local_18 = basic_string<>(local_8);
  FUN_0070f570(param_2,param_3);
  return param_2;
}

