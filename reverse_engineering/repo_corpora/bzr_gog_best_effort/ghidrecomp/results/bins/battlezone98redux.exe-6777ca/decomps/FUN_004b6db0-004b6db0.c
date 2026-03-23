
void FUN_004b6db0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar2 = FUN_00684ca0(0);
  if ((iVar2 != 0) && (DAT_008eaab0 != 0)) {
    local_c = *(undefined4 *)(&DAT_0260d79c + param_1 * 4);
    FUN_00430590();
    local_14 = DAT_00920ef4;
    puVar3 = (undefined4 *)FUN_0042d8c0(local_18);
    local_8 = *puVar3;
    while( true ) {
      uVar4 = FID_conflict_begin(local_20);
      cVar1 = FUN_00420f10(uVar4);
      if (cVar1 == '\0') break;
      piVar5 = (int *)FUN_0042de50();
      local_10 = *(int **)(*piVar5 + 4);
      (**(code **)(*local_10 + 0x18))();
      DAT_00920ef4 = local_14;
      FUN_00438c10(local_1c,0);
    }
    if (0 < DAT_0091756c) {
      FUN_0068c0f0(DAT_00917580,DAT_0091756c,DAT_009175a0,DAT_009175a4,0x250001,0);
      DAT_0091756c = 0;
    }
  }
  return;
}

