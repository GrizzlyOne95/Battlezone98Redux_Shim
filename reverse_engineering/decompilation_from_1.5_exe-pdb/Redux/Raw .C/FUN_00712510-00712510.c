
void __thiscall FUN_00712510(int param_1,undefined4 *param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  *(int *)(param_1 + 0x10) = param_4;
  local_10 = param_4;
  local_8 = param_1;
  if (param_4 == 1) {
    local_c = FUN_007139f0(param_2,*(undefined4 *)(param_1 + 0x14));
  }
  else {
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_3;
    cVar1 = FUN_004c85a0();
    if ((((cVar1 != '\0') && (param_3 == 0)) ||
        (local_c = FUN_007139f0(param_2,*(undefined4 *)(local_8 + 0x14)), local_c == 0)) ||
       (iVar3 = FUN_006ae390(local_8 + 8), *(int *)(local_8 + 0x14) == iVar3)) {
      FUN_0070e5b0(*param_2,param_2[1],*(undefined4 *)(local_8 + 0x14));
      return;
    }
  }
  iVar3 = local_8;
  uVar2 = FUN_006ae3b0(local_18,local_8 + 8,*(undefined4 *)(local_8 + 0x14),local_c,local_8);
  uVar2 = FUN_006ae430(local_20,uVar2);
  FUN_0071b280(uVar2,iVar3);
  return;
}

