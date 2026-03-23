
void FUN_00451ea0(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  int local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  
  FUN_00447e20(local_c);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_1c);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_10 = FUN_00447e70();
    FUN_00447e90();
    FUN_00423890();
    puVar3 = (undefined4 *)FUN_00447e20(local_20);
    local_8 = *puVar3;
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50(local_24);
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_14 = FUN_00447e70();
      *(undefined4 *)(local_14 + 0x68) = 0xbdcccccd;
      FUN_00447e90();
    }
  }
  FUN_0044e700();
  FUN_004518c0();
  return;
}

