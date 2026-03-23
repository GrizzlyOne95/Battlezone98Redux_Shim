
undefined4 FUN_005ce3a0(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  int local_8;
  
  local_10 = DAT_00917a74;
  FID_conflict_begin(local_c);
  do {
    uVar2 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    iVar4 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
    if ((iVar4 == param_2) &&
       (iVar4 = (*(code *)**(undefined4 **)(local_8 + 0x18))(), *(int *)(iVar4 + 0x14) == 0x434e5354
       )) {
      local_14 = local_8;
      iVar4 = FUN_005c74f0();
      if (iVar4 == param_1) {
        return 1;
      }
    }
    FUN_0046b260(local_18,0);
  } while( true );
}

