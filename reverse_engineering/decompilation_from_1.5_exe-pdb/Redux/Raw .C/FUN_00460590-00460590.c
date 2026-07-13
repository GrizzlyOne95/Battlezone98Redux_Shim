
void __fastcall FUN_00460590(int *param_1)

{
  undefined1 local_18 [4];
  void *local_14;
  void *local_10;
  int local_c;
  int *local_8;
  
  local_8 = param_1;
  FUN_0045e060(param_1);
  local_c = local_8[5];
  FUN_0042d920(local_18,local_c);
  if (*local_8 != 0) {
    local_10 = (void *)*local_8;
    operator_delete__(local_10);
  }
  local_14 = (void *)local_8[2];
  operator_delete__(local_14);
  return;
}

