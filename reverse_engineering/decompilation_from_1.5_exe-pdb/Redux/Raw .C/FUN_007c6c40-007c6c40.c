
void __thiscall FUN_007c6c40(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int local_10;
  int local_c;
  int *local_8;
  
  local_10 = param_2;
  local_c = param_3;
  local_8 = param_1;
  if ((param_1[7] != param_2) || (param_1[8] != param_3)) {
    param_1[7] = param_2;
    param_1[8] = param_3;
    (**(code **)(*param_1 + 0x20))(&local_10);
  }
  (**(code **)(*local_8 + 0x24))(&local_10,param_4);
  return;
}

