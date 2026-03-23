
void __thiscall FUN_0049c3e0(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  
  if ((*(int *)(param_1 + 0x68) != 0) && (DAT_02cecf74 == 0)) {
    iVar2 = FUN_004978d0();
    uVar1 = DAT_00920ef4;
    if (iVar2 == 0) {
      fVar3 = (float10)FUN_0049c320(param_1 + 0x28,4);
      DAT_00920ef4 = (float)fVar3;
      FUN_0068e600(param_2,param_1 + 0x58,*(undefined4 *)(param_1 + 100),
                   *(undefined4 *)(param_1 + 0x68),4);
      DAT_00920ef4 = (float)uVar1;
    }
    else {
      FUN_00820180(param_1 + 0x28,param_1 + 0x28,5,param_2 + 0x40);
      uVar1 = DAT_00920ef4;
      fVar3 = (float10)FUN_0049c320(param_1 + 0x28,4);
      DAT_00920ef4 = (float)fVar3;
      FUN_0068d2f0(param_2,*(undefined4 *)(param_1 + 0x68),param_1 + 0x28,4);
      DAT_00920ef4 = (float)uVar1;
    }
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  return;
}

