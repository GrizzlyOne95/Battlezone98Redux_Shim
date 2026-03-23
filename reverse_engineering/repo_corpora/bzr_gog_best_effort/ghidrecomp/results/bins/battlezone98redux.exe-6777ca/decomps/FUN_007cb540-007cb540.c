
void __fastcall FUN_007cb540(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0066b150();
  iVar2 = size();
  if (*(int *)(param_1 + 0x150) < iVar1 - iVar2) {
    *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + 1;
    FUN_007cb400();
  }
  return;
}

