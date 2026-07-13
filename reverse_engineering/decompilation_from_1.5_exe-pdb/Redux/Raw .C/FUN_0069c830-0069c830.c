
/* WARNING: Removing unreachable block (ram,0x0069c8f4) */

void FUN_0069c830(char *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 local_424;
  uint local_420;
  undefined4 local_41c;
  undefined4 local_418;
  char *local_414;
  undefined4 local_410;
  int local_40c;
  void *local_408;
  char *local_404;
  char *local_400;
  char *local_3fc;
  char *local_3f8;
  char local_3f4;
  char local_3f3;
  char local_3f2;
  char local_3f1 [1001];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_424 = 0;
  local_40c = FUN_00481af0(param_1);
  if (local_40c == 0) {
    local_410 = 0;
    local_3f1[1] = 0;
    local_404 = local_3f1;
    do {
      local_3f3 = local_404[1];
      local_404 = local_404 + 1;
    } while (local_3f3 != '\0');
    pcVar4 = "Error Opening parse file: \'";
    pcVar5 = local_404;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar5 = pcVar5 + 4;
    }
    local_3f8 = param_1;
    local_414 = param_1;
    do {
      local_3f4 = *local_3f8;
      local_3f8 = local_3f8 + 1;
    } while (local_3f4 != '\0');
    local_420 = (int)local_3f8 - (int)param_1;
    local_400 = local_3f1;
    do {
      local_3f1[0] = local_400[1];
      local_400 = local_400 + 1;
    } while (local_3f1[0] != '\0');
    pcVar4 = local_400;
    for (uVar3 = local_420 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)param_1;
      param_1 = param_1 + 4;
      pcVar4 = pcVar4 + 4;
    }
    for (uVar3 = local_420 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar4 = *param_1;
      param_1 = param_1 + 1;
      pcVar4 = pcVar4 + 1;
    }
    local_3fc = local_3f1;
    do {
      local_3f2 = local_3fc[1];
      local_3fc = local_3fc + 1;
    } while (local_3f2 != '\0');
    local_3fc[0] = '\'';
    local_3fc[1] = '\0';
    FUN_00699180(local_3f1 + 1,1);
  }
  else {
    uVar1 = FUN_00481a60(param_1);
    FUN_0069c1e0(local_40c,uVar1,&local_408,&local_418);
    FUN_00481990(param_1);
    local_41c = FUN_0069c150(local_408,&local_424,local_418,param_2);
    free(local_408);
  }
  FUN_0083e885();
  return;
}

