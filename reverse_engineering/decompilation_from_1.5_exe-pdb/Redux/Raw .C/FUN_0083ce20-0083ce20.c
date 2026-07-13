
void FUN_0083ce20(int *param_1,int *param_2)

{
  if (*param_2 == 0xd) {
    *param_2 = 0xc;
    param_2[2] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4) >> 6 & 0xff;
  }
  else if (*param_2 == 0xe) {
    *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4) =
         *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4) & 0x7fffff | 0x1000000;
    *param_2 = 0xb;
  }
  return;
}

