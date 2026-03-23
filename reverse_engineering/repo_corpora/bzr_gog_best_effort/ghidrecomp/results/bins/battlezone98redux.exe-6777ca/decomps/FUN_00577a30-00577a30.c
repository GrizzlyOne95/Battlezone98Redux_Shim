
undefined1 __thiscall FUN_00577a30(undefined4 param_1,undefined2 param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_005771b0(param_2,param_1);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar3 = (uint)*(byte *)(iVar2 + 0x68);
    FUN_005e0bc0(DAT_00917f50,uVar3);
    uVar1 = FUN_005e1310(uVar3);
  }
  return uVar1;
}

