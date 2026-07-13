
void __fastcall FUN_0066c5f0(int *param_1)

{
  int iVar1;
  int *piVar2;
  int local_c;
  
  piVar2 = (int *)FUN_00417780(*param_1);
  local_c = *piVar2;
  piVar2 = (int *)FUN_00417780(*param_1);
  *piVar2 = *param_1;
  piVar2 = (int *)FUN_004242e0(*param_1);
  *piVar2 = *param_1;
  param_1[1] = 0;
  while (local_c != *param_1) {
    piVar2 = (int *)FUN_00417780(local_c);
    iVar1 = *piVar2;
    FUN_0066d440(local_c);
    local_c = iVar1;
  }
  return;
}

