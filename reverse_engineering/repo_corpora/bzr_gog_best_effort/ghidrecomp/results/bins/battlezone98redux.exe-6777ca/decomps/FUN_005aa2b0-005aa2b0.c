
void FUN_005aa2b0(undefined4 *param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (7 < param_2) {
    piVar1 = (int *)FUN_004b9ab0(*param_1);
    iVar2 = FUN_004b9ab0(param_1[1]);
    if ((piVar1 != (int *)0x0) && (iVar2 != 0)) {
      uVar3 = (**(code **)(piVar1[6] + 0x30))();
      iVar4 = FUN_004626a0(uVar3);
      if (iVar4 != 0) {
        (**(code **)(*piVar1 + 100))(iVar2);
      }
    }
  }
  return;
}

