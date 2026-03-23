
void FUN_0062d410(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != 0) {
    *(int *)(param_1 + 0x78) = param_2;
    *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_2 + 0x80);
    *(int *)(param_2 + 0x80) = param_1;
    *(undefined2 *)(param_1 + 0x10) = *(undefined2 *)(param_2 + 0x10);
    iVar1 = *(ushort *)(param_2 + 0x12) - 1;
    *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + (short)iVar1;
    for (param_1 = *(int *)(param_1 + 0x80); param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
      FUN_0062d3b0(param_1,iVar1,param_2);
    }
  }
  return;
}

