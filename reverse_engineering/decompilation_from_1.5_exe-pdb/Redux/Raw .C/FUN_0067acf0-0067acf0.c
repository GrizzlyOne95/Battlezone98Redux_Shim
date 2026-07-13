
void __thiscall FUN_0067acf0(int *param_1,undefined4 param_2)

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
      FUN_0067b290(1);
    }
    FUN_00422c10(param_1[1],param_1[1]);
    uVar2 = FUN_00417780(param_2);
    iVar4 = param_1[1];
    Getal(&local_6);
    construct<>(iVar4,uVar2);
    param_1[1] = param_1[1] + 8;
  }
  else {
    iVar3 = FUN_00417780(param_2);
    iVar4 = *param_1;
    if (param_1[1] == param_1[2]) {
      FUN_0067b290(1);
    }
    FUN_00422c10(param_1[1],param_1[1]);
    uVar2 = FUN_00417780(*param_1 + (iVar3 - iVar4 >> 3) * 8);
    iVar4 = param_1[1];
    Getal(&local_5);
    construct<>(iVar4,uVar2);
    param_1[1] = param_1[1] + 8;
  }
  return;
}

