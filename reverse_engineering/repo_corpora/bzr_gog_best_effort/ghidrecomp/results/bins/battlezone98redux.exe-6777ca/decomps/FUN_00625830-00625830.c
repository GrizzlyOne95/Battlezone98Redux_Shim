
undefined2 FUN_00625830(float param_1)

{
  undefined2 uVar1;
  
  if (param_1 <= 127.0) {
    if (param_1 < -127.0) {
      param_1 = -127.0;
    }
  }
  else {
    param_1 = 127.0;
  }
  floor((double)(param_1 * 256.0) + 0.5);
  uVar1 = FUN_0083f040();
  return uVar1;
}

