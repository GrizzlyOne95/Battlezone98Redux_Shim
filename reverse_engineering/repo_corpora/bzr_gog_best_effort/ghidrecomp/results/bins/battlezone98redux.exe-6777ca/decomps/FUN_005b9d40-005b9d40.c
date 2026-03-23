
void __fastcall FUN_005b9d40(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 0xc) = 4;
  }
  else if (iVar1 == 2) {
    FUN_00601070();
  }
  else if (iVar1 == 3) {
    FUN_006028d0();
  }
  return;
}

