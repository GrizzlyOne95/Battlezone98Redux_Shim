
void FUN_0083c488(int *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  if ((*param_2 == 0xb) &&
     (uVar1 = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4), ((byte)uVar1 & 0x3f) == 0x13)) {
    param_1[6] = param_1[6] + -1;
    FUN_0083c5d2(param_1,0x1a,uVar1 >> 0x17,0,param_3 == 0);
    FUN_0083c9bd(param_1);
  }
  else {
    FUN_0083c15a(param_1,param_2);
    FUN_0083c3b1(param_1,param_2);
    FUN_0083c5d2(param_1,0x1b,0xff,param_2[2],param_3);
    FUN_0083c9bd(param_1);
  }
  return;
}

