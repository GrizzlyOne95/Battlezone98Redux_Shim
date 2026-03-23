
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005f91e0(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  float10 fVar7;
  
  iVar2 = FUN_00417c70();
  if (iVar2 != 0) {
    iVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
    iVar4 = (**(code **)(*(int *)(iVar2 + 0x18) + 4))();
    if ((((iVar3 == iVar4) && ((*(int *)(param_1 + 0xcc) == 0 || (*(int *)(param_1 + 200) == 0))))
        && ((param_2 != DAT_02cc31b0 ||
            ((cVar1 = FUN_005f91b0(param_2), cVar1 == '\0' &&
             (fVar7 = (float10)FUN_00822d80(), 1.0 <= (float)fVar7 - _DAT_02cc31ac)))))) &&
       ((((param_2 != 0x17 && (param_2 != 0x16)) ||
         (fVar7 = (float10)FUN_00822d80(), 5.0 <= (float)fVar7 - _DAT_009182a8)) &&
        ((((pcVar5 = (char *)FUN_005f8fb0(param_1,param_2,param_3), pcVar5 != (char *)0x0 &&
           (*pcVar5 != '\0')) && (cVar1 = FUN_00437da0(), cVar1 == '\0')) &&
         (iVar3 = FUN_0061a050(), iVar3 == 0)))))) {
      uVar6 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))(0);
      FUN_0043d1d0(pcVar5,uVar6);
      DAT_02cc31b0 = param_2;
      fVar7 = (float10)FUN_00822d80();
      _DAT_02cc31ac = (float)fVar7;
    }
  }
  return;
}

