
void __thiscall FUN_00732bc0(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_006d0da0();
  uVar2 = FUN_006d0d10(iVar1 + (*(int *)(param_1 + 4) - param_2) * 0x20,param_2);
  FUN_006dcea0(uVar2);
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) - param_2;
  return;
}

