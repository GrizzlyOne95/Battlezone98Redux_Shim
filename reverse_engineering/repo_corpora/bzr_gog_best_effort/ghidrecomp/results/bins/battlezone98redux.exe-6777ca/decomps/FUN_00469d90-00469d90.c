
void FUN_00469d90(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = FUN_0077d680();
  local_8 = DAT_02ce99c0;
  local_c = DAT_02cd9984;
  local_10 = 0;
  do {
    if (param_1 <= local_10) {
      return;
    }
    cVar1 = FUN_00468980(local_8,local_c);
    if (cVar1 == '\0') {
      *(byte *)(DAT_0260d178 + local_10) = *(byte *)(DAT_0260d178 + local_10) & 0xfc;
      cVar1 = FUN_00468890(local_8,local_c);
      if (cVar1 == '\0') {
        cVar1 = FUN_00468450(local_8,local_c);
        if (cVar1 != '\0') {
          *(byte *)(DAT_0260d178 + local_10) = *(byte *)(DAT_0260d178 + local_10) | 1;
        }
      }
      else {
        *(byte *)(DAT_0260d178 + local_10) = *(byte *)(DAT_0260d178 + local_10) | 2;
      }
    }
    else {
      *(byte *)(DAT_0260d178 + local_10) = *(byte *)(DAT_0260d178 + local_10) | 3;
    }
    iVar3 = FUN_0077d660(local_8,local_c);
    if (iVar3 == iVar2) {
LAB_00469f67:
      *(byte *)(DAT_0260d178 + local_10) = *(byte *)(DAT_0260d178 + local_10) | 4;
    }
    else {
      iVar3 = FUN_0077d660(local_8 + -1,local_c + -1);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8,local_c + -1);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8 + 1,local_c + -1);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8 + -1,local_c);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8 + 1,local_c);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8 + -1,local_c + 1);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8,local_c + 1);
      if (iVar3 == iVar2) goto LAB_00469f67;
      iVar3 = FUN_0077d660(local_8 + 1,local_c + 1);
      if (iVar3 == iVar2) goto LAB_00469f67;
    }
    local_8 = local_8 + 1;
    if (DAT_02ce99a0 <= local_8) {
      local_8 = DAT_02ce99c0;
      local_c = local_c + 1;
      if (DAT_02ce99c4 <= local_c) {
        local_c = DAT_02cd9984;
      }
    }
    local_10 = local_10 + 1;
  } while( true );
}

