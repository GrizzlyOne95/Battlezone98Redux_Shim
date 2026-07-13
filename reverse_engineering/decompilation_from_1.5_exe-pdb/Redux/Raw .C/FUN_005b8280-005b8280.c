
uint __fastcall FUN_005b8280(uint param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_c;
  
  iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x18) + 0x18))();
  if (*(int *)(iVar1 + 0x14) == 0x52435943) {
    uVar2 = (**(code **)(**(int **)(param_1 + 0x18) + 0x68))();
    if ((uVar2 & 0xff) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
      param_1 = uVar2;
      goto LAB_005b8343;
    }
  }
  FUN_00462590();
  iVar1 = FUN_005e10b0();
  iVar3 = FUN_005e1190();
  if (iVar1 < iVar3) {
    local_c = FUN_005b50e0();
    FUN_005b50a0(local_c);
    iVar1 = FUN_00572a70();
    if (iVar1 != 0) {
      local_c = local_c << 1;
    }
    FUN_005e1010(local_c);
  }
  *(undefined4 *)(param_1 + 0xc) = 0xd;
LAB_005b8343:
  return param_1 & 0xffffff00;
}

