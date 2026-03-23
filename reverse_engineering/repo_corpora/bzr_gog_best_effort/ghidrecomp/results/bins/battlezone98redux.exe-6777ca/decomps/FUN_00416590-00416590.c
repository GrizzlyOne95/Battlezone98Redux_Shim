
undefined4 FUN_00416590(undefined4 param_1,int param_2)

{
  char *local_c;
  
  local_c = std::_Syserror_map(param_2);
  if (local_c == (char *)0x0) {
    local_c = "unknown error";
  }
  basic_string<>(local_c);
  return param_1;
}

