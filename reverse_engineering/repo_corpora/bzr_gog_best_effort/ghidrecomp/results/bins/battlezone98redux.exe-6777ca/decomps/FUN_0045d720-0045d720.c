
char FUN_0045d720(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 auStack_48 [12];
  undefined4 uStack_3c;
  undefined1 *puStack_38;
  undefined1 *puStack_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  uint local_18;
  int *local_14;
  undefined1 local_10 [4];
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  if (DAT_009173b7 == '\0') {
    puStack_34 = local_10;
    puStack_38 = (undefined1 *)0x45d74b;
    FUN_0042d8c0();
    while (local_5 != '\0') {
      puStack_34 = local_20;
      puStack_38 = (undefined1 *)0x45d772;
      puStack_34 = (undefined1 *)FID_conflict_begin();
      puStack_38 = (undefined1 *)0x45d77b;
      cVar1 = FUN_00420f10();
      if (cVar1 == '\0') break;
      puStack_34 = (undefined1 *)0x45d78a;
      puVar2 = (undefined4 *)FUN_0042de50();
      local_14 = (int *)*puVar2;
      puStack_34 = (undefined1 *)0x45d79c;
      local_5 = (**(code **)(*local_14 + 8))();
      puStack_34 = (undefined1 *)0x0;
      puStack_38 = local_1c;
      uStack_3c = 0x45d75b;
      FUN_00438c10();
    }
    if (*(char *)(local_c + 0x10) != '\0') {
      local_18 = (uint)(*(char *)(local_c + 0x18) == '\0');
      puStack_34 = (undefined1 *)local_18;
      puStack_38 = (undefined1 *)0x45d7d0;
      FUN_00434170();
      if (*(char *)(local_c + 0x19) == '\0') {
        local_24 = auStack_48;
        local_28 = basic_string<>("nofile");
        FUN_00487b40();
      }
      else {
        local_2c = auStack_48;
        local_30 = basic_string<>(local_c + 0x19);
        FUN_00487b40();
      }
    }
  }
  return local_5;
}

