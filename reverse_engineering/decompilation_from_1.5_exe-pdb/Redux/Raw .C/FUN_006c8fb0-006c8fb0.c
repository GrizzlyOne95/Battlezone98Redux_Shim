
void __fastcall FUN_006c8fb0(int *param_1)

{
  int iVar1;
  int local_c;
  int *local_8;
  
  if (*param_1 != 0) {
    local_c = *param_1;
    local_8 = param_1;
    iVar1 = FUN_006dc6f0(*param_1);
    *local_8 = iVar1;
    if (*local_8 == 0) {
      local_8[1] = 0;
    }
    FUN_006dc700(&local_c,0);
  }
  return;
}

