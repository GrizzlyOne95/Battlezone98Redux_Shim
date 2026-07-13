
int FUN_0045c990(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  int local_c;
  int *local_8;
  
  local_c = 0;
  local_10 = 0;
  do {
    if ((1 < local_10) || (local_c != 0)) {
      DAT_00915694 = local_c;
      return local_c;
    }
    FUN_0042d8c0(local_14);
    while( true ) {
      uVar2 = FID_conflict_begin(local_1c);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_0042de50();
      local_8 = (int *)*puVar3;
      iVar4 = (**(code **)*local_8)(param_1);
      if (iVar4 != 0) {
        local_c = (**(code **)(*local_8 + 4))();
        break;
      }
      FUN_00438c10(local_18,0);
    }
    param_1 = "empty";
    local_10 = local_10 + 1;
  } while( true );
}

