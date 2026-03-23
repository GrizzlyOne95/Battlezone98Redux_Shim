
int __fastcall FUN_006b1fa0(undefined4 *param_1)

{
  int local_c;
  
  local_c = FUN_006b20f0(param_1 + 2,0,0);
  if (local_c == 0) {
    local_c = FUN_006d9060(*param_1);
    FUN_006b2110(param_1 + 2,local_c);
  }
  return local_c;
}

