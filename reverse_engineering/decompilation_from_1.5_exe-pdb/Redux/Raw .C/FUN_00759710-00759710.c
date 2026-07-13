
uint FUN_00759710(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint in_EAX;
  uint uVar1;
  
  if (param_3 < 0x481) {
    uVar1 = FUN_007592d0(param_1,param_2,param_3,param_4);
  }
  else {
    uVar1 = in_EAX & 0xffffff00;
  }
  return uVar1;
}

