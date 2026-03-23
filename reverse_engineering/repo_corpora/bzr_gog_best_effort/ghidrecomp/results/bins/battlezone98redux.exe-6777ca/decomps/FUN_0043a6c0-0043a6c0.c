
undefined4 FUN_0043a6c0(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    iVar2 = FUN_0043c920(param_1,&local_8);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      iVar2 = FUN_0043c800(param_1);
      if (iVar2 == 0) {
        FUN_007d6830("Can\'t create DS3D primary buffer. 3D sound disabled");
        uVar1 = 1;
      }
      else {
        iVar2 = FUN_0043a680(param_1,DAT_008e765c);
        if (iVar2 == 0) {
          FUN_0043c710(param_1);
          uVar1 = 1;
        }
        else {
          iVar2 = FUN_0043c740(param_1);
          if (iVar2 == 0) {
            FUN_007d6830("Can\'t create DS3D listener. 3D sound disabled");
            uVar1 = 1;
          }
          else {
            FUN_0043e980();
            uVar1 = 1;
          }
        }
      }
    }
  }
  return uVar1;
}

