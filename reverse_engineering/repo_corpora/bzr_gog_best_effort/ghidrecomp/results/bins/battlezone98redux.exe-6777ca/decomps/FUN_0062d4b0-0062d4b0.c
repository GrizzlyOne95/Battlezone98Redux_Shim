
void FUN_0062d4b0(int param_1)

{
  int iVar1;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = FUN_00618b60(param_1);
  if (iVar1 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = *(ushort *)(iVar1 + 0x12) - 1;
    if (*(int *)(iVar1 + 0x80) == param_1) {
      *(undefined4 *)(iVar1 + 0x80) = *(undefined4 *)(param_1 + 0x7c);
    }
    else {
      for (local_c = *(int *)(iVar1 + 0x80); local_c != 0; local_c = *(int *)(local_c + 0x7c)) {
        if (*(int *)(local_c + 0x7c) == param_1) {
          *(undefined4 *)(local_c + 0x7c) = *(undefined4 *)(param_1 + 0x7c);
          break;
        }
      }
    }
  }
  *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) - (short)local_10;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  for (param_1 = *(int *)(param_1 + 0x80); param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
    FUN_0062d3b0(param_1,-local_10,iVar1);
  }
  return;
}

