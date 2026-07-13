
void FUN_006176a0(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_8;
  
  uVar2 = FUN_0062c840();
  iVar3 = ___scrt_is_user_matherr_present(uVar2);
  local_8 = (uint)(iVar3 == 0);
  if (DAT_00915650 == 0) {
    iVar3 = FUN_00824250(uVar2,local_8);
    if (iVar3 != 0) {
      FUN_00824270(param_1);
    }
    FUN_00616e50();
    FUN_00616e80(param_1);
    FUN_00617600(param_1,uVar2,local_8);
    if ((((DAT_008eaad8 == 3) || (DAT_008eaad8 == 9)) || (DAT_008eaad8 == 10)) ||
       (DAT_009454bc != 0)) {
      FUN_0067cb10(0,0,0);
    }
    FUN_005dddc0();
    FUN_005d6500();
    if (((DAT_008eaad8 != 9) && (DAT_008eaad8 != 3)) &&
       ((DAT_008eaad8 != 10 && (DAT_009454bc == 0)))) {
      uVar1 = FUN_005d6130();
      FUN_00616500(param_1,uVar1);
    }
    FUN_00780c70(param_1);
    if ((DAT_008eaad8 != 9) && (DAT_008eaad8 != 10)) {
      FUN_00584d30(param_1);
      FUN_0062eab0(param_1);
      FUN_004d4610(param_1);
    }
  }
  return;
}

