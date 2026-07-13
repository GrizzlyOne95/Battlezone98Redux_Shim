
uint FUN_0045c3c0(undefined4 param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  uint in_EAX;
  uint uVar1;
  undefined4 local_c [2];
  
  if (param_3 == 4) {
    local_c[0] = *param_2;
    uVar1 = FUN_004ccd80(param_1,local_c,4,param_4);
  }
  else {
    uVar1 = in_EAX & 0xffffff00;
  }
  return uVar1;
}

