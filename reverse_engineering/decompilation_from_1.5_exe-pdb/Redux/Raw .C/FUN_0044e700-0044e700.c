
void FUN_0044e700(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  int *local_18;
  int *local_14;
  int *local_10;
  undefined4 local_c;
  char local_5;
  
  FUN_00430590();
  DAT_0091552a = 1;
  do {
    local_5 = '\0';
    puVar2 = (undefined4 *)FUN_0044ea80(local_24);
    local_c = *puVar2;
    while( true ) {
      uVar3 = FUN_0044eaa0(local_28);
      cVar1 = FUN_00420f10(uVar3);
      if (cVar1 == '\0') break;
      iVar4 = FUN_0042da60();
      if (*(char *)(*(int *)(iVar4 + 4) + 0x100) != '\0') {
        iVar4 = FUN_0042da60();
        local_18 = *(int **)(iVar4 + 4);
        local_14 = local_18;
        local_10 = local_18;
        if (local_18 == (int *)0x0) {
          local_1c = 0;
        }
        else {
          local_1c = (**(code **)(*local_18 + 4))(1);
        }
        local_20 = local_c;
        FUN_0044eac0(local_2c,local_c);
        local_5 = '\x01';
        break;
      }
      FUN_0042da80();
    }
    if (local_5 == '\0') {
      DAT_0091552a = 0;
      return;
    }
  } while( true );
}

