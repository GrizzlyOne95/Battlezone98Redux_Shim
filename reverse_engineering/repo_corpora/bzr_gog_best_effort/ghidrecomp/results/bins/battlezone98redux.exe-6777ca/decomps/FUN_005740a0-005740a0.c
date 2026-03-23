
/* WARNING: Removing unreachable block (ram,0x0057438f) */
/* WARNING: Removing unreachable block (ram,0x005742d1) */
/* WARNING: Removing unreachable block (ram,0x00574293) */
/* WARNING: Removing unreachable block (ram,0x00574358) */
/* WARNING: Removing unreachable block (ram,0x005743c6) */

void FUN_005740a0(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4,
                 undefined4 param_5,int param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  size_t sVar5;
  undefined *local_50;
  undefined *local_4c;
  undefined *local_48;
  undefined *local_40;
  undefined *local_38;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b7a8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  iVar2 = FUN_00573d00(param_1,param_2,param_3,param_4,param_5,param_6,param_7,0,uVar1);
  if (iVar2 == 4) {
    DAT_00917f78 = param_1;
    DAT_00917f7b = 1;
    DAT_00917f8e = *(char *)(param_6 + 0x50);
    DAT_009175bf = *(char *)(param_6 + 0x60);
    DAT_008e8c0e = *(char *)(param_6 + 0x52);
    DAT_008e8d04 = *(undefined4 *)(param_6 + 0x58);
    DAT_00917fa4 = *(undefined4 *)(param_6 + 0x58);
    DAT_008e7733 = *(char *)(param_6 + 0x51);
    DAT_008e8c0c = *(char *)(param_6 + 0x68);
    DAT_00917f44 = *(undefined4 *)(param_6 + 0x54);
    DAT_00917f54 = *(undefined4 *)(param_6 + 100);
    DAT_00917f50 = *(undefined4 *)(param_7 + 0x2c);
    if (DAT_008e8c0c == '\0') {
      local_48 = &DAT_00884424;
    }
    else {
      local_48 = &DAT_00884428;
    }
    if (DAT_008e7733 == '\0') {
      local_50 = &DAT_00884424;
    }
    else {
      local_50 = &DAT_00884428;
    }
    if (DAT_008e8c0e == '\0') {
      local_38 = &DAT_00884424;
    }
    else {
      local_38 = &DAT_00884428;
    }
    if (DAT_009175bf == '\0') {
      local_4c = &DAT_00884424;
    }
    else {
      local_4c = &DAT_00884428;
    }
    if (DAT_00917f8e == '\0') {
      local_40 = &DAT_00884424;
    }
    else {
      local_40 = &DAT_00884428;
    }
    uVar3 = FUN_0041f870(local_40,local_4c,local_38,local_50,local_48,DAT_00917fa4,DAT_00917f44,
                         DAT_00917f54);
    uVar3 = FUN_0041f870(uVar3);
    uVar3 = FUN_0041f870(uVar3);
    uVar3 = FUN_0081e820("Launching Network Game %s, Map %s, Workshop %s, Sync: %s, Sniper: %s, Barracks: %s, CommSat: %s, Splint: %s, Lives: %d, Time: %d, Kills %d\n"
                         ,uVar3);
    FUN_0081e710(uVar3);
    sVar5 = 10;
    pcVar4 = (char *)FUN_0041f870();
    strncpy(&DAT_008e8c74,pcVar4,sVar5);
    DAT_008e8c7d = 0;
    sVar5 = 100;
    pcVar4 = (char *)FUN_0041f870();
    strncpy(s_unnamed_008e8c80,pcVar4,sVar5);
    DAT_008e8ce3 = 0;
    uVar3 = FUN_0073a9f0(local_2c);
    local_8 = 0;
    uVar3 = FUN_0041f870(uVar1,uVar3);
    FUN_007d6a70("Net: Launching game with local user ID information as %u (remote %s)\n",
                 *(undefined2 *)(param_7 + 0x10),uVar3);
    local_8 = 0xffffffff;
    ~basic_string<>();
    sVar5 = 0x10;
    pcVar4 = (char *)FUN_0041f870();
    strncpy(&DAT_00915540,pcVar4,sVar5);
    DAT_0091554f = 0;
    strncpy(&DAT_00917f58,&DAT_00915540,0x14);
    DAT_00917f6b = 0;
    strncpy(&DAT_008e8c10,&DAT_00915540,100);
    DAT_008e8c73 = 0;
    DAT_009180cc = *(undefined4 *)(param_7 + 100);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

