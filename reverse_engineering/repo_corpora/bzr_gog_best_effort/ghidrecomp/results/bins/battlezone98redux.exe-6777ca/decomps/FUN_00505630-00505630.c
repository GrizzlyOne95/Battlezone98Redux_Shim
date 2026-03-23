
undefined4 FUN_00505630(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  double dVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  uint uVar3;
  float10 fVar4;
  
  fVar4 = (float10)FUN_0082d3e1(param_3,param_4);
  dVar1 = (double)fVar4;
  if (dVar1 == 0.0) {
    uVar2 = CONCAT31(CONCAT21(extraout_var,(dVar1 == 0.0) << 6 | NAN(dVar1) << 2 | 2U | dVar1 < 0.0)
                     ,1);
  }
  else {
    uVar3 = (uint)fVar4;
    if (dVar1 == (double)(int)uVar3) {
      if (((int)uVar3 < -0x80) || (0x7f < (int)uVar3)) {
        if (((int)uVar3 < -0x8000) || (0x7fff < (int)uVar3)) {
          uVar2 = FUN_00505590(param_1,param_2,uVar3);
        }
        else {
          uVar2 = FUN_00505540(param_1,param_2,uVar3 & 0xffff);
        }
      }
      else {
        uVar2 = FUN_005054f0(param_1,param_2,uVar3 & 0xff);
      }
    }
    else {
      uVar2 = FUN_005055e0(param_1,param_2,dVar1);
    }
  }
  return uVar2;
}

