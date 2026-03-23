
int __fastcall FUN_00733310(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_00713d00(param_1[1]);
  return *(int *)(*(int *)(*param_1 + 4) + iVar1 * 4) + (uint)param_1[1] % 0x10;
}

