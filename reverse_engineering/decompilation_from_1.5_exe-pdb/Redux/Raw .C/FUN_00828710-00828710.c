
void FUN_00828710(void)

{
  uint uVar1;
  int iVar2;
  undefined4 local_8;
  
  uVar1 = FUN_00829680();
  for (local_8 = 0; local_8 < uVar1; local_8 = local_8 + 1) {
    iVar2 = FUN_008296a0(local_8);
    if (*(int *)(iVar2 + 0x1000) != 0) {
      iVar2 = FUN_008296a0(local_8);
      FUN_00827310(*(undefined4 *)(iVar2 + 0x1000));
      iVar2 = FUN_008296a0(local_8);
      *(undefined4 *)(iVar2 + 0x1000) = 0;
    }
  }
  return;
}

