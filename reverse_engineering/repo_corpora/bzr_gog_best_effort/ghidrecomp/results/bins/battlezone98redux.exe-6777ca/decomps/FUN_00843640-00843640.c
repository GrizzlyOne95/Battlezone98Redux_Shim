
uint FUN_00843640(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = 0;
  local_4 = FUN_0083e820();
  iVar1 = FUN_008435a0(param_1,&local_8);
  uVar3 = 0;
  if (iVar1 == 0) {
    uVar3 = local_8;
  }
  uVar2 = FUN_00842d80(uVar3,param_1,param_2,"boost::filesystem::remove");
  if ((char)uVar2 != '\0') {
    return uVar2 & 0xffffff00;
  }
  uVar2 = FUN_00843750(param_1,iVar1,param_2);
  return uVar2;
}

