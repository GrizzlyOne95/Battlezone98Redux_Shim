
void FUN_005c19d0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_14 = DAT_00917a74;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  local_10 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_20);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_8 = *piVar4;
    uVar5 = FUN_0045c4b0();
    if ((uVar5 & 1) == 0) {
      iVar6 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
      if (*(int *)(iVar6 + 0x1c) != 2) {
        cVar1 = FUN_0046fbf0();
        if (cVar1 == '\0') {
          FUN_005c1810();
          uVar3 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
          FUN_005c17c0(uVar3);
          for (local_c = 1; local_c < 0x10; local_c = local_c + 1) {
            cVar1 = FUN_004db560(local_c);
            if (cVar1 != '\0') {
              FUN_005c17c0(local_c);
            }
          }
        }
        else {
          FUN_004d97d0();
        }
      }
    }
    else {
      FUN_005c1810();
      uVar5 = FUN_0045c4b0();
      if ((uVar5 & 0x10) != 0) {
        uVar3 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
        FUN_005c17c0(uVar3);
      }
    }
    iVar6 = FUN_005c18a0();
    if (iVar6 != 0) {
      uVar3 = FUN_00461430();
      FUN_005c17c0(uVar3);
    }
    FUN_0046b260(local_1c,0);
  }
  return;
}

