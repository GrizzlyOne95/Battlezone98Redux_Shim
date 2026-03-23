
char FUN_004ce4e0(undefined4 param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uStack0000000c;
  undefined4 local_10;
  uint local_c;
  undefined1 local_7;
  undefined1 local_6;
  char local_5;
  
  uStack0000000c = 4;
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,0,4);
    FUN_004ce0b0();
    iVar2 = sscanf(DAT_0260db08,"%*s =");
    local_5 = iVar2 == 0;
    FUN_004ce120();
    FUN_004ce180();
    if (local_5 != '\0') {
      for (local_c = 0; local_c < uStack0000000c; local_c = local_c + 1) {
        local_7 = FUN_004ce180();
        local_6 = FUN_004ce180();
        uVar1 = FUN_004ce390(local_7,local_6);
        *(undefined1 *)((int)&local_10 + local_c) = uVar1;
      }
      FUN_004ce100();
    }
  }
  else {
    local_5 = FUN_004cdda0(0,4,&local_10);
  }
  if (local_5 == '\0') {
    local_10 = 0;
  }
  *param_2 = local_10;
  return local_5;
}

