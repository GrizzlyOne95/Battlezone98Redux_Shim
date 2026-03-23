
bool __thiscall FUN_007c6f30(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  DAT_00920e90 = *(float *)(param_2 + 4);
  if (1.0 < DAT_00920e90) {
    DAT_00920e90 = 0.06666667;
  }
  iVar2 = FUN_0044d2a0(param_1);
  cVar1 = (**(code **)(**(int **)(iVar2 + 0xc) + 0x140))();
  return cVar1 == '\0';
}

