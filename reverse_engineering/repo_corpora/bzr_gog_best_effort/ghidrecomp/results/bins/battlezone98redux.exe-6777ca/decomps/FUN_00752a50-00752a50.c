
void FUN_00752a50(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c148;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00752ed0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  puVar4 = local_2c;
  FUN_00764790(puVar4);
  FUN_004bb540(puVar4);
  local_8._0_1_ = 1;
  do {
    puVar4 = local_38;
    FUN_00764790(puVar4);
    local_20 = FUN_004bb570(puVar4);
    local_8._0_1_ = 2;
    local_1c = local_20;
    local_11 = FID_conflict_operator<(local_20);
    local_8._0_1_ = 1;
    FUN_004bb3b0();
    if (local_11 == '\0') {
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004bb3b0();
      local_8 = 0xffffffff;
      ~basic_string<>();
      ExceptionList = local_10;
      return;
    }
    cVar1 = FUN_00427270(&stack0x00000004,"All Maps");
    if (cVar1 == '\0') {
      cVar1 = FUN_00427270(&stack0x00000004,"Strategy");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'S') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Strategy");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'M') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Death Match");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'D') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Death Match");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'A') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,&DAT_0089b420);
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (*(char *)(iVar2 + 0x38) == 'K') goto LAB_00752cc4;
      }
      cVar1 = FUN_00427270(&stack0x00000004,"2 Players");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (1 < *(int *)(iVar2 + 0x1c)) {
          iVar2 = FUN_00752f10();
          if (*(int *)(iVar2 + 0x18) < 3) goto LAB_00752cc4;
        }
      }
      cVar1 = FUN_00427270(&stack0x00000004,"3 Players");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (2 < *(int *)(iVar2 + 0x1c)) {
          iVar2 = FUN_00752f10();
          if (*(int *)(iVar2 + 0x18) < 4) goto LAB_00752cc4;
        }
      }
      cVar1 = FUN_00427270(&stack0x00000004,"4 Players");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10();
        if (3 < *(int *)(iVar2 + 0x1c)) {
          iVar2 = FUN_00752f10();
          if (*(int *)(iVar2 + 0x18) < 5) goto LAB_00752cc4;
        }
      }
      cVar1 = FUN_00427270(&stack0x00000004,"Workshop");
      if (cVar1 != '\0') {
        iVar2 = FUN_00752f10(&DAT_00873c74);
        cVar1 = operator!=<>(iVar2 + 0x3c);
        if (cVar1 != '\0') goto LAB_00752cc4;
      }
    }
    else {
LAB_00752cc4:
      uVar3 = FUN_00752ef0();
      FUN_00752dd0(uVar3);
    }
    FUN_00732df0();
  } while( true );
}

