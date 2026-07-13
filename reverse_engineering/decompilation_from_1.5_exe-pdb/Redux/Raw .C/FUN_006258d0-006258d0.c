
undefined1 FUN_006258d0(float param_1)

{
  undefined1 uVar1;
  
  if (param_1 <= 1.0) {
    if (param_1 < -1.0) {
      param_1 = -1.0;
    }
  }
  else {
    param_1 = 1.0;
  }
  floor((double)(param_1 * 127.0) + 0.5);
  uVar1 = FUN_0083f040();
  return uVar1;
}

