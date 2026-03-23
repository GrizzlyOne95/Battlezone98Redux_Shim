
undefined4 FUN_007daad0(undefined8 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int local_c;
  uint local_8;
  
  FUN_007d72b0(param_1,&local_c);
  uVar2 = local_8 & 0x7fffffff;
  if (uVar2 < 0x100000) {
    if (local_c == 0 && uVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 0xfffffffe;
    }
  }
  else if ((uVar2 < 0x7ff00001) && (uVar2 < 0x7ff00000)) {
    uVar1 = 0xffffffff;
  }
  else if (local_c == 0 && (local_8 & 0xfffff) == 0) {
    uVar1 = 1;
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

