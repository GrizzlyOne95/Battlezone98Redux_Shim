
void FUN_00750bd0(char param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined1 local_18 [8];
  int *local_10;
  int local_c;
  byte local_5;
  
  cVar1 = FUN_00742cf0();
  if (cVar1 != '\0') {
    if (param_1 == '\0') {
      FUN_0081e820("Lobby ",local_c + 0x28," unlocked\n");
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_0073ba70(uVar2);
      FUN_004bc590(uVar2);
    }
    else {
      FUN_0081e820("Lobby ",local_c + 0x28," locked\n");
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_0073ba70(uVar2);
      FUN_004bc590(uVar2);
    }
    local_5 = param_1 == '\0';
    local_10 = (int *)FUN_007508c0();
    uVar4 = (uint)local_5;
    puVar3 = (undefined4 *)FUN_0073a970(local_18);
    (**(code **)(*local_10 + 0x88))(*puVar3,puVar3[1],uVar4);
  }
  return;
}

