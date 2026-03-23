
int __thiscall FUN_005c9530(undefined4 param_1,int param_2,int param_3)

{
  undefined4 in_EAX;
  uint3 uVar2;
  int iVar1;
  
  uVar2 = (uint3)((uint)in_EAX >> 8);
  if ((param_2 < 0) || (0xf < param_2)) {
    iVar1 = (uint)uVar2 << 8;
  }
  else if ((param_3 < 0) || (0xf < param_3)) {
    iVar1 = (uint)uVar2 << 8;
  }
  else {
    iVar1 = FUN_005e0bc0(param_2,param_1);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_005e1310(param_3);
    }
  }
  return iVar1;
}

