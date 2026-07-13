
undefined4 FUN_004cf210(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int local_18;
  uint local_14;
  int local_10;
  uint local_c;
  char local_6;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,7,param_3);
    FUN_004ce0b0();
    iVar3 = sscanf(DAT_0260db08,"%*s [%d] =",&local_18);
    local_6 = iVar3 == 1;
    local_14 = (uint)(byte)local_6;
    FUN_004ce100();
    for (local_10 = 0; local_10 < local_18; local_10 = local_10 + 1) {
      FUN_004ce0b0();
      puVar1 = (undefined4 *)(param_2 + local_10 * 8);
      *puVar1 = 0;
      puVar1[1] = 0;
      if (*DAT_0260db08 != '\0') {
        local_5 = 0;
        local_c = 0;
        while (((local_c < 8 && (DAT_0260db08[local_c] != '\0')) &&
               (iVar3 = isspace((int)DAT_0260db08[local_c]), iVar3 == 0))) {
          local_5 = 1;
          *(char *)(param_2 + local_10 * 8 + local_c) = DAT_0260db08[local_c];
          local_c = local_c + 1;
        }
      }
      FUN_004ce100();
      if (local_6 == '\0') {
        return 0;
      }
    }
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004cdda0(7,param_3,param_2);
  }
  return uVar2;
}

