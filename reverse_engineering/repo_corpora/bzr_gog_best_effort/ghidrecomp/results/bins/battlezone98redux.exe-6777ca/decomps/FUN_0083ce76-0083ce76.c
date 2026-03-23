
void FUN_0083ce76(int *param_1,int *param_2,int param_3)

{
  uint *puVar1;
  
  if (*param_2 == 0xd) {
    puVar1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4);
    *puVar1 = *puVar1 ^ ((param_3 + 1) * 0x4000 ^
                        *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4)) & 0x7fc000;
  }
  else if (*param_2 == 0xe) {
    *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4) =
         (param_3 + 1) * 0x800000 ^ *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4) & 0x7fffff;
    puVar1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4);
    *puVar1 = *puVar1 ^ (param_1[9] << 6 ^ *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4)) &
                        0x3fc0;
    FUN_0083cd31(param_1,1);
  }
  return;
}

