
undefined4 FUN_0046ad30(int param_1,int param_2)

{
  undefined4 uVar1;
  
  param_2 = param_2 - DAT_02cd9984;
  if ((param_2 < 0) || (DAT_02ce99c4 - DAT_02cd9984 <= param_2)) {
    uVar1 = 0;
  }
  else {
    param_1 = param_1 - DAT_02ce99c0;
    if ((param_1 < 0) || (DAT_02ce99a0 - DAT_02ce99c0 <= param_1)) {
      uVar1 = 0;
    }
    else {
      uVar1 = CONCAT22((short)((uint)DAT_0260d180 >> 0x10),
                       *(undefined2 *)
                        (DAT_0260d180 + ((DAT_02ce99a0 - DAT_02ce99c0) * param_2 + param_1) * 2));
    }
  }
  return uVar1;
}

