
void __fastcall FUN_00703dc0(int *param_1)

{
  int iVar1;
  int local_c;
  
  if (*param_1 != 0) {
    local_c = FUN_00417780(*param_1);
    while (iVar1 = param_1[2], param_1[2] = param_1[2] + -1, iVar1 != 0) {
      FUN_006ef1c0(param_1[1],local_c);
      local_c = local_c + 0x20;
    }
  }
  return;
}

