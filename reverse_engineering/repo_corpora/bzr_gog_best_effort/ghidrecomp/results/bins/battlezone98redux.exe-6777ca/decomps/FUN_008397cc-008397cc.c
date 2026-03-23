
void FUN_008397cc(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x30);
  *(char *)((int)piVar1 + 0x32) = *(char *)((int)piVar1 + 0x32) + (char)param_2;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    *(int *)((uint)*(ushort *)
                    ((int)piVar1 + ((uint)*(byte *)((int)piVar1 + 0x32) - param_2) * 2 + 0xac) * 0xc
             + 4 + *(int *)(*piVar1 + 0x18)) = piVar1[6];
  }
  return;
}

