
bool FUN_005cd1d0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    bVar3 = false;
  }
  else {
    iVar2 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
    if (*(int *)(iVar2 + 0x14) == 0x54554700) {
      bVar3 = *(int *)(iVar1 + 0x300) != 0;
    }
    else {
      bVar3 = false;
    }
  }
  return bVar3;
}

