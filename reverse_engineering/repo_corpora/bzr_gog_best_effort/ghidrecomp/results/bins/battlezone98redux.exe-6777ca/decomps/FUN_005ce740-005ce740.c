
int __thiscall FUN_005ce740(int *param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int local_c;
  
  if (param_1[1] <= param_2) {
    if (param_1[1] == 0) {
      iVar2 = FUN_0083d92c(0x140);
      *param_1 = iVar2;
      param_1[1] = 0x10;
    }
    else {
      iVar2 = param_1[1];
      lVar1 = (ulonglong)(uint)(iVar2 << 1) * 0x14;
      iVar3 = FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
      for (local_c = 0; local_c < param_1[1]; local_c = local_c + 1) {
        puVar4 = (undefined4 *)(*param_1 + local_c * 0x14);
        puVar5 = (undefined4 *)(local_c * 0x14 + iVar3);
        *puVar5 = *puVar4;
        puVar5[1] = puVar4[1];
        puVar5[2] = puVar4[2];
        puVar5[3] = puVar4[3];
        puVar5[4] = puVar4[4];
      }
      operator_delete((void *)*param_1);
      *param_1 = iVar3;
      param_1[1] = iVar2 << 1;
    }
  }
  return param_2 * 0x14 + *param_1;
}

