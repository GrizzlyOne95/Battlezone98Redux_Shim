
undefined4 FUN_0048fd00(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  
  bVar1 = FUN_0046acc0(param_1,param_2);
  if (((DAT_00915566 ^ bVar1) & DAT_008e7730) == 0) {
    uVar2 = FUN_0046ad30(param_1,param_2);
    if (((DAT_009173b0 ^ uVar2) & DAT_009173b4) == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

