
undefined4 FUN_004fd090(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  undefined4 local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  cVar1 = FUN_00571c40();
  if (cVar1 != '\0') {
    DAT_008e80b4 = 1;
    local_c = FUN_00417c70();
    local_14 = DAT_00917a74;
    FID_conflict_begin(local_10);
    while( true ) {
      uVar2 = FID_conflict_end(local_20);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      local_8 = *piVar3;
      local_18 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
      if (((*(int *)(local_18 + 0x14) != 0x5350574e) && (*(int *)(local_18 + 0x14) != 0x4745495a))
         && (local_c != local_8)) {
        cVar1 = FUN_00571c30();
        if (cVar1 == '\0') {
          FUN_004b9c30();
        }
        else {
          FUN_004b9bd0();
        }
      }
      FUN_0046b260(local_1c,0);
    }
    if (local_c != 0) {
      (**(code **)(*(int *)(local_c + 0x18) + 0x10))();
    }
  }
  return 1;
}

