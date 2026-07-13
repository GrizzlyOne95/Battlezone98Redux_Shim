
void __thiscall FUN_0045ba50(uint *param_1,int param_2)

{
  void *pvVar1;
  uint uVar2;
  uint uVar3;
  uint local_c;
  
  uVar3 = param_2 + param_1[3] & param_1[4];
  if (param_1[1] < uVar3) {
    pvVar1 = (void *)param_1[2];
    uVar2 = FUN_0083d92c(-(uint)((int)((ulonglong)uVar3 * 4 >> 0x20) != 0) |
                         (uint)((ulonglong)uVar3 * 4));
    param_1[2] = uVar2;
    if (pvVar1 != (void *)0x0) {
      for (local_c = 0; local_c < *param_1; local_c = local_c + 1) {
        *(undefined4 *)(param_1[2] + local_c * 4) = *(undefined4 *)((int)pvVar1 + local_c * 4);
      }
      operator_delete__(pvVar1);
    }
    param_1[1] = uVar3;
  }
  return;
}

