
void FUN_0083b0a4(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x30);
  while (param_2 < (int)(uint)*(byte *)((int)piVar1 + 0x32)) {
    *(char *)((int)piVar1 + 0x32) = *(char *)((int)piVar1 + 0x32) + -1;
    *(int *)((uint)*(ushort *)((int)piVar1 + (uint)*(byte *)((int)piVar1 + 0x32) * 2 + 0xac) * 0xc +
             8 + *(int *)(*piVar1 + 0x18)) = piVar1[6];
  }
  return;
}

