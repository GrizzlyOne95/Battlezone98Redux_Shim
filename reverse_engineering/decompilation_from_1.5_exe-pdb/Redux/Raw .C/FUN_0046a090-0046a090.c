
void FUN_0046a090(int param_1,uint *param_2,ushort param_3)

{
  ushort uVar1;
  uint local_c;
  
  for (local_c = 0; local_c < *param_2; local_c = local_c + 1) {
    if (param_3 == *(ushort *)(param_1 + local_c * 2)) {
      return;
    }
    if (param_3 < *(ushort *)(param_1 + local_c * 2)) break;
  }
  for (; local_c < *param_2; local_c = local_c + 1) {
    uVar1 = *(ushort *)(param_1 + local_c * 2);
    *(ushort *)(param_1 + local_c * 2) = param_3;
    param_3 = uVar1;
  }
  *(ushort *)(param_1 + *param_2 * 2) = param_3;
  *param_2 = *param_2 + 1;
  return;
}

