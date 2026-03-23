
undefined1 __thiscall FUN_005b5d60(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_44;
  
  cVar2 = FUN_004cf520(param_2,param_1 + 0x2c,4,&DAT_00886704);
  if ((cVar2 == '\0') || (cVar2 = FUN_004cf520(param_2,param_1 + 0x30,4,"subtask"), cVar2 == '\0'))
  {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd520(param_2,param_1 + 0x34,0xc,"lastScrap"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x40,4,"scrapHandle"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x44,4,"dropHandle"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x48,4,"curState"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x4c,4,"nextState"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd520(param_2,param_1 + 0x50,0xc,"where"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x5c,4,"nextCheck"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd520(param_2,param_1 + 0x60,0xc,"lastRecyclerPos"), cVar2 != '\0')
     ) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x18,4,"nextStuck"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd520(param_2,param_1 + 0x1c,0xc,"lastStuck"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x28,4,"stuckState"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_00461c90(param_2), cVar2 != '\0')) {
    local_44 = 1;
  }
  else {
    local_44 = 0;
  }
  return local_44;
}

