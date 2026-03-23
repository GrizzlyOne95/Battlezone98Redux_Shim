
undefined4 FUN_004fffd0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint local_8;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = (*(code *)**(undefined4 **)(iVar2 + 0x18))();
    for (local_8 = 0; (local_8 < 8 && (*(char *)(iVar2 + 0x30 + local_8) != '\0'));
        local_8 = local_8 + 1) {
    }
    FUN_0082cd08(param_1,iVar2 + 0x30,local_8);
    uVar1 = 1;
  }
  return uVar1;
}

