
uint FUN_005fed30(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = FUN_00417ca0();
  if (iVar1 != 0) {
    uVar2 = FUN_00462510();
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      if ((1 << ((byte)local_c & 0x1f) & uVar2) != 0) {
        uVar3 = FUN_00417f60(local_c);
        local_8 = local_8 << 1 ^ uVar3;
        if (uVar3 != 0) {
          local_8 = local_8 ^ *(uint *)(uVar3 + 0xc) ^ *(uint *)(*(int *)(uVar3 + 8) + 0xc);
        }
      }
    }
  }
  return local_8;
}

