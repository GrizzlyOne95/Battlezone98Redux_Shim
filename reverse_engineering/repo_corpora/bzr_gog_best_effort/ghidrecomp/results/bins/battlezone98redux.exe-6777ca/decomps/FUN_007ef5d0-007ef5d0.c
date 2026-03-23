
uint __thiscall
FUN_007ef5d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_007ef400(param_6,param_1);
  if ((uVar1 & 0xff) == 0) {
    uVar1 = uVar1 & 0xffffff00;
  }
  else {
    uVar2 = FUN_00423b10(param_6);
    uVar3 = FUN_007ef550(uVar2);
    uVar1 = FUN_007eff10(uVar3);
    if ((uVar1 & 0xff) == 0) {
      uVar1 = uVar1 & 0xffffff00;
    }
    else {
      uVar2 = FUN_006db910(uVar2);
      uVar1 = FUN_007ede50(param_3,param_4,param_5,uVar2);
    }
  }
  return uVar1;
}

