
void FUN_005999f0(undefined4 *param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  int local_20;
  int local_1c;
  int *local_18;
  undefined *local_14;
  undefined4 local_10;
  int *local_c;
  int local_8;
  
  local_14 = &DAT_0094de1c;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_24);
  local_10 = *puVar2;
  do {
    uVar3 = FID_conflict_begin(local_2c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      *param_1 = 0;
      *param_2 = -1;
      return;
    }
    puVar2 = (undefined4 *)FUN_0042de50();
    local_c = (int *)*puVar2;
    if (*local_c != 0) {
      for (local_8 = 0; local_8 < local_c[1]; local_8 = local_8 + 1) {
        (**(code **)(*local_18 + 0x24))
                  (*(undefined4 *)(local_c[2] + local_8 * 8),
                   *(undefined4 *)(local_c[2] + 4 + local_8 * 8),&local_1c,&local_20);
        iVar4 = FUN_00594280(local_1c - DAT_009175a0);
        if ((iVar4 < 4) && (iVar4 = FUN_00594280(local_20 - DAT_009175a4), iVar4 < 4)) {
          *param_1 = local_c;
          *param_2 = local_8;
          return;
        }
      }
    }
    FUN_00438c10(local_28,0);
  } while( true );
}

