
uint FUN_004d35b0(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined4 local_8;
  
  FUN_00430590();
  puVar1 = (undefined4 *)FUN_0042d8c0(local_14);
  local_8 = *puVar1;
  while( true ) {
    uVar2 = FID_conflict_begin(local_1c);
    uVar3 = FUN_00420f10(uVar2);
    if ((uVar3 & 0xff) == 0) {
      return uVar3 & 0xffffff00;
    }
    local_10 = (int *)FUN_0042de50();
    if (*local_10 == param_1) break;
    FUN_00438c10(local_18,0);
  }
  return CONCAT31((int3)((uint)*local_10 >> 8),(char)local_10[1]);
}

