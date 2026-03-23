
void FUN_0074ca30(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00420260(local_8);
  FUN_00430590();
  FID_conflict_begin(local_14);
  FUN_00420260(local_c);
  FID_conflict_begin(local_18);
  do {
    cVar1 = FUN_00420f10(local_18);
    if (cVar1 == '\0') {
      while( true ) {
        cVar1 = FUN_00420f10(local_14);
        if (cVar1 == '\0') break;
        puVar3 = (undefined4 *)FUN_004305b0(local_30,0);
        local_20 = *puVar3;
        local_10 = local_20;
        FUN_006d6800(local_34,local_20);
      }
      FUN_0074cb90(param_1);
      return;
    }
    while( true ) {
      cVar1 = FUN_00420f10(local_14);
      if (cVar1 == '\0') break;
      uVar2 = FUN_00422150();
      FUN_00422150(uVar2);
      cVar1 = FUN_00574a30(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_004305b0(local_28,0);
      local_1c = *puVar3;
      local_10 = local_1c;
      FUN_006d6800(local_2c,local_1c);
    }
    cVar1 = FUN_00420f10(local_14);
    if (cVar1 != '\0') {
      uVar2 = FUN_00422150();
      FUN_00422150(uVar2);
      cVar1 = FUN_0056f780(uVar2);
      if (cVar1 != '\0') {
        FUN_00428570();
      }
    }
    FUN_00428570();
  } while( true );
}

