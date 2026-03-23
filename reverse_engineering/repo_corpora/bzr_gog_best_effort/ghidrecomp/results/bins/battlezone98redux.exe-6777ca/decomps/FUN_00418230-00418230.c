
undefined1 FUN_00418230(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_c;
  
  iVar1 = FUN_00417c70();
  if (iVar1 == 0) {
    local_c = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    iVar3 = FUN_00417e20(uVar2);
    if (iVar3 == 0) {
      local_c = 0;
    }
    else if ((iVar1 == 0) || (*(int *)(iVar1 + 0xec) == 0)) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}

