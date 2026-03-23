
void __fastcall FUN_00472060(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 2) {
    FUN_00601200();
  }
  else if (iVar1 == 3) {
    FUN_00602920();
  }
  else if (iVar1 == 5) {
    (**(code **)(**(int **)(param_1 + 0x10) + 100))();
  }
  return;
}

