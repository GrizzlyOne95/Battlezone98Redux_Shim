
int __thiscall FUN_006d4430(int param_1,undefined4 param_2,int param_3)

{
  undefined4 local_c;
  
  FUN_006b4800();
  *(undefined4 *)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 8) = 0;
  if (param_3 == 2) {
    local_c = cerr_exref;
  }
  else {
    local_c = cout_exref;
  }
  *(code **)(param_1 + 0xc) = local_c;
  return param_1;
}

