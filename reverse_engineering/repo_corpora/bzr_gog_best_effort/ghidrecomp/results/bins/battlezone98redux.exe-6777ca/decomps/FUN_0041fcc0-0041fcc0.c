
void __thiscall FUN_0041fcc0(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar2 = FUN_00417780(param_2);
  cVar1 = FUN_00422af0(uVar2);
  if (cVar1 == '\0') {
    if (param_1[1] == param_1[2]) {
      FUN_00422b30(1);
    }
    FUN_00422c10(param_1[1],param_1[1]);
    iVar4 = param_1[1];
    Getal(&local_6);
    construct<>(iVar4,param_2);
    param_1[1] = param_1[1] + 0x94;
  }
  else {
    iVar3 = FUN_00417780(param_2);
    iVar4 = *param_1;
    if (param_1[1] == param_1[2]) {
      FUN_00422b30(1);
    }
    FUN_00422c10(param_1[1],param_1[1]);
    iVar3 = ((iVar3 - iVar4) / 0x94) * 0x94 + *param_1;
    iVar4 = param_1[1];
    Getal(&local_5);
    construct<>(iVar4,iVar3);
    param_1[1] = param_1[1] + 0x94;
  }
  return;
}

