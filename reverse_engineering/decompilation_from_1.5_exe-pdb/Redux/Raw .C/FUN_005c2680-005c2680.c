
int * FUN_005c2680(int param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  
  piVar2 = (int *)FUN_00463120(param_1);
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    uVar3 = (**(code **)(piVar2[6] + 0xc))();
    uVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(uVar3);
    fVar5 = (float10)FUN_00462010(uVar3);
    if ((float)fVar5 <= 1600.0) {
      iVar4 = (**(code **)piVar2[6])();
      if ((*(int *)(iVar4 + 0x14) == 0x52435943) &&
         (cVar1 = (**(code **)(*piVar2 + 0x68))(), cVar1 == '\0')) {
        piVar2 = (int *)0x0;
      }
    }
    else {
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}

