
void __fastcall FUN_004b9890(int *param_1)

{
  int iVar1;
  int *local_c;
  
  if (param_1 == (int *)0x0) {
    local_c = (int *)0x0;
  }
  else {
    local_c = param_1 + -6;
  }
  local_c[0x3b] = 0;
  iVar1 = (**(code **)(*param_1 + 0x30))();
  if (iVar1 != 0) {
    FUN_0062de40(iVar1,0x280);
  }
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined2 *)((int)param_1 + 0x62) = 0;
  FUN_004badc0(param_1 + 0x19);
  FUN_004b7bd0();
  iVar1 = (**(code **)*param_1)();
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x14) == 0x53435250)) {
    (**(code **)(*param_1 + 0x10))();
  }
  return;
}

