
void __thiscall FUN_006f4ec0(int param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_44 [28];
  undefined1 local_28 [28];
  int local_c;
  int local_8;
  
  *(int *)(param_1 + 0x24) = param_4;
  local_c = param_4;
  local_8 = param_1;
  if (param_4 == 1) {
    uVar2 = FUN_006b2da0(param_2,*(undefined4 *)(param_1 + 0x28));
    FUN_006f66c0(uVar2);
LAB_006f4eff:
    FUN_006ff310(local_8 + 4,local_8);
  }
  else {
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + param_3;
    FUN_006f66e0(param_3);
    uVar2 = FUN_006b2da0(param_2,*(undefined4 *)(local_8 + 0x28));
    FUN_006f66c0(uVar2);
    cVar1 = FUN_004c85a0();
    if ((cVar1 == '\0') || (param_3 != 0)) {
      uVar2 = FUN_006f66a0(local_28);
      uVar3 = FUN_006f6650(local_44);
      cVar1 = FUN_006f68b0(uVar3,uVar2);
      if (cVar1 == '\0') goto LAB_006f4eff;
    }
    FUN_006fecf0(param_2,local_8 + 0x28);
  }
  return;
}

