
undefined4 FUN_0083d02b(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  undefined4 uVar3;
  
  puVar2 = (uint *)FUN_0083c410(param_1,param_2);
  uVar1 = *puVar2;
  if (((byte)uVar1 & 0x3f) == 0x1b) {
    if ((param_3 == 0xff) || (param_3 == uVar1 >> 0x17)) {
      *puVar2 = (uVar1 & 0xffb5ffff | 0x340000) >> 0x11 | uVar1 & 0x7fc000;
    }
    else {
      *puVar2 = (param_3 << 6 ^ uVar1) & 0x3fc0 ^ uVar1;
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

