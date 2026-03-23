
void __thiscall FUN_0047c540(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = FUN_005cd290();
  if ((cVar1 == '\0') && (*(int *)(param_1 + 300) != 0)) {
    **(int **)(param_1 + 300) = param_1 + 0x130 + param_2 * 0x10;
    *(int *)(param_1 + 300) = *(int *)(param_1 + 300) + 4;
    if (param_1 + 0x128U <= *(uint *)(param_1 + 300)) {
      *(int *)(param_1 + 300) = param_1 + 0x28;
    }
  }
  return;
}

