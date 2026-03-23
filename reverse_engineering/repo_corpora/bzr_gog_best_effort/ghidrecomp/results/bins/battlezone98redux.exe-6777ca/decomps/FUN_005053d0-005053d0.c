
void FUN_005053d0(int *param_1,undefined4 param_2)

{
  undefined4 uStack_8;
  
  if ((*(byte *)(*param_1 + -1) & 0x1f) == 0) {
    uStack_8 = 0;
  }
  else {
    uStack_8 = 0x1000000;
  }
  FUN_0082cbf5(param_2,uStack_8 >> 0x18);
  return;
}

