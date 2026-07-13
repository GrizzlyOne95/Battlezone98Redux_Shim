
void FUN_004b0190(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *local_248;
  char *local_244;
  int local_240;
  undefined4 local_23c;
  undefined *local_234 [4];
  undefined *local_224;
  undefined *local_220;
  undefined *local_21c;
  undefined *local_218;
  undefined4 local_214;
  char local_210 [260];
  char local_10c [260];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_234[0] = &DAT_00878498;
  local_234[1] = &DAT_008784ac;
  local_234[2] = &DAT_008784a8;
  local_234[3] = &DAT_0087848c;
  local_224 = &DAT_00878488;
  local_220 = &DAT_00878494;
  local_21c = &DAT_00878490;
  local_218 = &DAT_008784cc;
  local_214 = 0;
  if (DAT_009174e4 != 0) {
    FUN_004afe50("mission %s\n",param_1);
  }
  uVar2 = FUN_004afde0("2.2.301",7,0);
  if (DAT_009174e4 != 0) {
    FUN_004afe50("version %08x (%s)\n",uVar2,"2.2.301");
  }
  local_248 = param_1;
  pcVar5 = local_210;
  local_244 = pcVar5;
  do {
    cVar1 = *local_248;
    *local_244 = cVar1;
    local_248 = local_248 + 1;
    local_244 = local_244 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strchr(local_210,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  local_23c = FUN_004b0170(uVar2,pcVar5);
  local_240 = 0;
  while (local_234[local_240] != (undefined *)0x0) {
    sprintf(local_10c,"%s.%s",local_210,local_234[local_240]);
    local_240 = local_240 + 1;
    iVar4 = FUN_00829390(local_10c);
    if (iVar4 != 0) {
      local_23c = FUN_004aff40(local_10c,local_23c);
    }
  }
  sprintf(local_10c,"%s.dep",local_210);
  iVar4 = FUN_00829390(local_10c);
  if (iVar4 != 0) {
    FUN_004afff0(local_10c,local_23c);
  }
  FUN_0083e885();
  return;
}

