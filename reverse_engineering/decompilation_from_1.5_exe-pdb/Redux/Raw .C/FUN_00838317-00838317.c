
void FUN_00838317(undefined4 param_1)

{
  DWORD DVar1;
  char *pcVar2;
  undefined4 uVar3;
  CHAR local_110 [264];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DVar1 = GetModuleFileNameA((HMODULE)0x0,local_110,0x105);
  if ((DVar1 != 0) && (DVar1 != 0x105)) {
    pcVar2 = strrchr(local_110,0x5c);
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
      uVar3 = FUN_0082d377(param_1,0xffffffff,0,&DAT_0086ff54,local_110);
      FUN_0082bd93(param_1,uVar3);
      FUN_0082cf99(param_1,0xfffffffe);
      goto LAB_0083839e;
    }
  }
  FUN_0082bc39(param_1,"unable to get ModuleFileName");
LAB_0083839e:
  FUN_0083e885();
  return;
}

