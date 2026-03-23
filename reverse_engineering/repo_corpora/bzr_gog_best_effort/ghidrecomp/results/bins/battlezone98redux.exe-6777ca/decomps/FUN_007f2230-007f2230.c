
void FUN_007f2230(undefined4 param_1,undefined8 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar3 = (undefined4)param_2;
  uVar4 = (undefined4)((ulonglong)param_2 >> 0x20);
  cVar1 = FUN_007f3150(uVar3,uVar4);
  if (cVar1 == '\0') {
    cVar1 = FUN_007f31e0(uVar3,uVar4);
    if (cVar1 == '\0') {
      FUN_007f3270(param_1,uVar3,uVar4,param_3);
    }
    else {
      uVar2 = FUN_006dc8e0(uVar3,uVar4);
      FUN_007f3200(param_1,uVar3,uVar4,uVar2);
    }
  }
  else {
    uVar2 = FUN_006dc8e0(uVar3,uVar4);
    FUN_007f3170(param_1,uVar3,uVar4,uVar2);
  }
  return;
}

