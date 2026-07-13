
/* WARNING: Removing unreachable block (ram,0x004fd82f) */

void FUN_004fd7e0(undefined4 param_1)

{
  bool bVar1;
  char cVar2;
  char *_Source;
  size_t _Count;
  undefined4 uVar3;
  char local_3c [49];
  undefined1 uStack_b;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(local_3c,0,0x32);
  _Count = 0x32;
  FUN_00482850();
  _Source = (char *)FUN_0041f870();
  strncpy(local_3c,_Source,_Count);
  uVar3 = 0x31;
  uStack_b = 0;
  cVar2 = FUN_004cce90(param_1,local_3c,0x32,"nPlayerSide");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd1b0(param_1,&DAT_0091830c,4,"nMissionStatus"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_1,&DAT_00918314,4,"nOldMissionMode"), cVar2 != '\0')) {
    cVar2 = '\x01';
  }
  else {
    cVar2 = '\0';
  }
  FUN_0083e885(uVar3,cVar2,cVar2 != '\0');
  return;
}

