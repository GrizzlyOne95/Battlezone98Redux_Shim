
undefined1
FUN_0043a0c0(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  undefined1 uVar1;
  float fVar2;
  
  fVar2 = (param_4 - param_1) * (param_4 - param_1);
  if (fVar2 <= 22500.0) {
    fVar2 = (param_6 - param_3) * (param_6 - param_3) + fVar2;
    if (fVar2 <= 22500.0) {
      if ((param_5 - param_2) * (param_5 - param_2) + fVar2 <= 22500.0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

