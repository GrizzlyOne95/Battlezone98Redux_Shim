
void __thiscall FUN_0046b1a0(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))(param_1);
  piVar2 = (int *)(iVar1 + 0x1c);
  iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  iVar1 = *(int *)(iVar1 + 0x14);
  if (((((*piVar2 == 2) || (*piVar2 == 10)) || (*piVar2 == 5)) || (iVar1 == 0x54555252)) &&
     (((iVar1 != 0x50524f58 && (iVar1 != 0x4745495a)) &&
      ((iVar1 != 0x53464c44 && (iVar1 != 0x5350574e)))))) {
    FUN_00468a70(param_2,0);
  }
  return;
}

