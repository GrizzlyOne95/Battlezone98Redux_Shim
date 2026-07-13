
uint FUN_0046acc0(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_2 - DAT_02cd9984;
  if (((int)uVar1 < 0) || (DAT_02ce99c4 - DAT_02cd9984 <= (int)uVar1)) {
    uVar1 = uVar1 & 0xffffff00;
  }
  else {
    param_1 = param_1 - DAT_02ce99c0;
    uVar2 = uVar1;
    if ((param_1 < 0) || (uVar2 = DAT_02ce99a0 - DAT_02ce99c0, (int)uVar2 <= param_1)) {
      uVar1 = uVar2 & 0xffffff00;
    }
    else {
      uVar1 = CONCAT31((int3)(uVar2 >> 8),
                       *(undefined1 *)
                        (DAT_0260d178 + (DAT_02ce99a0 - DAT_02ce99c0) * uVar1 + param_1));
    }
  }
  return uVar1;
}

