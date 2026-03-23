
uint FUN_005cb4e0(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
    uVar2 = *(uint *)(iVar1 + 0x14);
    if ((((uVar2 == 0x52435943) || (uVar2 == 0x46414354)) || (uVar2 == 0x41524d52)) ||
       (uVar2 == 0x434e5354)) {
      uVar2 = FUN_004738b0();
    }
    else {
      uVar2 = uVar2 & 0xffffff00;
    }
  }
  return uVar2;
}

