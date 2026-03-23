
undefined4 __fastcall FUN_00603a70(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    iVar3 = FUN_00417e20(uVar2);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_00462670(iVar1);
    }
  }
  return uVar2;
}

