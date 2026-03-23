
void FUN_004cab60(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int *local_8;
  
  FUN_0042d8c0(local_c);
  while( true ) {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    FUN_00438c10(local_14,0);
    puVar3 = (undefined4 *)FUN_0042de50();
    local_8 = (int *)*puVar3;
    (**(code **)(*local_8 + 0x10))(param_1);
    if ((*(uint *)(local_8[3] + 0x14) & 0x200) != 0) {
      (**(code **)(*local_8 + 0xc))();
    }
  }
  return;
}

