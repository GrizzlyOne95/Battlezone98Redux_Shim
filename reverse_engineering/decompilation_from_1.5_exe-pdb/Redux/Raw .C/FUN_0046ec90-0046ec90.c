
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046ec90(char param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0046eaf0(param_2);
  iVar2 = (iVar1 - _DAT_0260d6c0) / DAT_0260d630;
  iVar1 = FUN_0046eaf0(param_3);
  iVar3 = (iVar1 - _DAT_0260d63c) / DAT_0260d630;
  iVar1 = FUN_0046eaf0(param_4);
  iVar1 = ((iVar1 - _DAT_0260d6c0) + -1 + DAT_0260d630) / DAT_0260d630;
  iVar4 = FUN_0046eaf0(param_5);
  iVar4 = ((iVar4 - _DAT_0260d63c) + -1 + DAT_0260d630) / DAT_0260d630;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  if (DAT_0260d638 < iVar1) {
    iVar1 = DAT_0260d638;
  }
  if (DAT_0260d6d4 < iVar4) {
    iVar4 = DAT_0260d6d4;
  }
  FUN_0046eb00(iVar1,iVar2,iVar3,iVar4);
  if (param_1 == '\0') {
    FUN_0046eb10(0,0,DAT_0260d638,iVar3);
    FUN_0046eb10(0,iVar4,DAT_0260d638,DAT_0260d6d4);
    FUN_0046eb10(0,iVar3,iVar2,iVar4);
    FUN_0046eb10(iVar1,iVar3,DAT_0260d638,iVar4);
  }
  else {
    FUN_0046eb10(iVar2,iVar3,iVar1,iVar4);
  }
  return;
}

