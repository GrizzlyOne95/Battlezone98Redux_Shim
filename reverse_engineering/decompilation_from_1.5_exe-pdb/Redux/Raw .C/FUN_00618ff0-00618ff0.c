
undefined4 FUN_00618ff0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_50;
  char *local_4c;
  char *local_48;
  char *local_44;
  char *local_40;
  char *local_3c;
  undefined4 *local_38;
  char *local_34;
  undefined4 *local_30;
  char *local_2c;
  undefined4 *local_28;
  char *local_24;
  char *local_20;
  undefined1 *local_1c;
  char *local_18;
  char *local_14;
  
  _getcwd(&DAT_02cf1000,0x1000);
  local_3c = &DAT_02cf1000;
  local_14 = &DAT_02cf0000;
  do {
    cVar2 = *local_3c;
    *local_14 = cVar2;
    local_3c = local_3c + 1;
    local_14 = local_14 + 1;
  } while (cVar2 != '\0');
  local_40 = &DAT_02cf1000;
  local_18 = &DAT_02cedf80;
  do {
    cVar2 = *local_40;
    *local_18 = cVar2;
    local_40 = local_40 + 1;
    local_18 = local_18 + 1;
  } while (cVar2 != '\0');
  local_1c = &DAT_02ceffff;
  do {
    pcVar1 = local_1c + 1;
    local_1c = local_1c + 1;
  } while (*pcVar1 != '\0');
  *local_1c = 0;
  local_44 = &DAT_02cf1000;
  local_20 = &DAT_02cf2000;
  do {
    cVar2 = *local_44;
    *local_20 = cVar2;
    local_44 = local_44 + 1;
    local_20 = local_20 + 1;
  } while (cVar2 != '\0');
  local_48 = &DAT_02cf1000;
  local_24 = &DAT_02ceefe0;
  do {
    cVar2 = *local_48;
    *local_24 = cVar2;
    local_48 = local_48 + 1;
    local_24 = local_24 + 1;
  } while (cVar2 != '\0');
  local_28 = (undefined4 *)((int)&DAT_02ceefd8 + 7);
  puVar3 = local_28;
  do {
    local_28 = puVar3;
    puVar3 = (undefined4 *)((int)local_28 + 1);
  } while (*(char *)((int)local_28 + 1) != '\0');
  *(undefined4 *)((int)local_28 + 1) = 0x7661735c;
  *(undefined2 *)((int)local_28 + 5) = 0x65;
  local_4c = &DAT_02cf1000;
  local_2c = (char *)&DAT_02cf3000;
  do {
    cVar2 = *local_4c;
    *local_2c = cVar2;
    local_4c = local_4c + 1;
    local_2c = local_2c + 1;
  } while (cVar2 != '\0');
  local_30 = (undefined4 *)&DAT_02cf2fff;
  puVar3 = local_30;
  do {
    local_30 = puVar3;
    puVar3 = (undefined4 *)((int)local_30 + 1);
  } while (*(char *)((int)local_30 + 1) != '\0');
  *(undefined4 *)((int)local_30 + 1) = 0x6464615c;
  *(undefined2 *)((int)local_30 + 5) = 0x6e6f;
  *(undefined1 *)((int)local_30 + 7) = 0;
  local_50 = &DAT_02cf1000;
  local_34 = (char *)&DAT_02cecf80;
  do {
    cVar2 = *local_50;
    *local_34 = cVar2;
    local_50 = local_50 + 1;
    local_34 = local_34 + 1;
  } while (cVar2 != '\0');
  local_38 = (undefined4 *)&DAT_02cecf7f;
  puVar3 = local_38;
  do {
    local_38 = puVar3;
    puVar3 = (undefined4 *)((int)local_38 + 1);
  } while (*(char *)((int)local_38 + 1) != '\0');
  *(undefined4 *)((int)local_38 + 1) = 0x646f6d5c;
  *(undefined2 *)((int)local_38 + 5) = 0x73;
  iVar4 = FUN_00618b70();
  if (iVar4 == 0) {
    FUN_00618c10(param_1,param_2,param_3);
    FUN_00619fc0();
    DAT_00920ecc = 0;
    FUN_0081e1e0("Starting Exit Game Cleanup\n");
    FUN_00618530();
    DAT_008eaaa4 = 0;
    FUN_00624110();
    FUN_0081e0c0("Exiting Game With Return Code %ld\n",DAT_009183d8);
    uVar5 = DAT_009183d8;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

