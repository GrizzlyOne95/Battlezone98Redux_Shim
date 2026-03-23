
void __thiscall FUN_0067a870(int param_1,undefined4 *param_2)

{
  int iVar1;
  code *local_c;
  
  if (*(char *)(param_1 + 0x12) == '\0') {
    local_c = (code *)(*(int *)(param_1 + 0x38) + 0x100);
  }
  else {
    local_c = IDENTITY_exref;
  }
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_2 = *(undefined4 *)local_c;
    local_c = local_c + 4;
    param_2 = param_2 + 1;
  }
  return;
}

