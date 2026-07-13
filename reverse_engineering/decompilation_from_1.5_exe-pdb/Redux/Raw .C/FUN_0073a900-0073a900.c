
int __fastcall FUN_0073a900(int *param_1)

{
  uint3 uVar2;
  int iVar1;
  
  uVar2 = (uint3)((uint)(param_1[2] | param_1[3]) >> 8);
  if ((param_1[2] | param_1[3]) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      FUN_0073a590(param_1[2],param_1[3]);
      iVar1 = FUN_0073a5d0();
    }
    else if (iVar1 == 2) {
      iVar1 = CONCAT31(uVar2,1);
    }
    else if (iVar1 == 3) {
      iVar1 = CONCAT31(uVar2,1);
    }
    else {
      iVar1 = (uint)uVar2 << 8;
    }
  }
  return iVar1;
}

