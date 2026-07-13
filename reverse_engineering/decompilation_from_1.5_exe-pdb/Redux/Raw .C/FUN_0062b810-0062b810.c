
void FUN_0062b810(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *local_8;
  
  local_8 = DAT_02a1f49c;
  while (local_8 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*local_8;
    iVar2 = FUN_0062d370(local_8[2],"Obj76\\Classfnc.c");
    if (iVar2 == 0) {
      FUN_0062c100(local_8);
      local_8 = puVar1;
    }
    else {
      iVar3 = FUN_0062be60(*(undefined4 *)(iVar2 + 0x84));
      local_8 = puVar1;
      if (*(int *)(&DAT_008ec7cc + iVar3 * 0x34) != 0) {
        (**(code **)(&DAT_008ec7cc + iVar3 * 0x34))(iVar2);
      }
    }
  }
  return;
}

