
void __fastcall FUN_004fa2a0(int param_1)

{
  int iVar1;
  undefined4 local_c;
  
  FUN_004c85d0();
  FUN_004c85d0();
  if (param_1 == 0) {
    local_c = 0;
  }
  else {
    local_c = param_1 + 0x28;
  }
  iVar1 = FUN_0044d2a0();
  (**(code **)(**(int **)(iVar1 + 8) + 0x324))(local_c);
  return;
}

