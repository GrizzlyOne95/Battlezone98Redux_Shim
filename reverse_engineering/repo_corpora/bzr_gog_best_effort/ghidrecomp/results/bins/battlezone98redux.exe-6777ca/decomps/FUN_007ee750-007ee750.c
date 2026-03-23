
int __thiscall FUN_007ee750(int param_1,int param_2)

{
  undefined4 local_10;
  undefined4 local_c;
  
  FUN_006e1cb0(param_2);
  if (param_2 == 0) {
    local_c = 0;
  }
  else {
    local_c = param_2 + 4;
  }
  FUN_006e1cb0(local_c);
  if (param_2 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = param_2 + 8;
  }
  FUN_007d7110(local_10);
  *(undefined1 *)(param_1 + 0x14) = *(undefined1 *)(param_2 + 0x14);
  return param_1;
}

