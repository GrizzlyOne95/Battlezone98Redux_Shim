
void __fastcall FUN_0056d8b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(param_1 + 0x3fc) = 1;
  *(undefined4 *)(param_1 + 0x400) = 1;
  *(undefined4 *)(param_1 + 0x404) = 1;
  *(undefined4 *)(param_1 + 0x408) = 1;
  cVar1 = FUN_005c84d0(param_1 + 1000);
  if (cVar1 == '\0') {
    uVar2 = FUN_005c8250("abstor",1,"goal1a",0,0);
    *(undefined4 *)(param_1 + 1000) = uVar2;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x3ec);
  if (cVar1 == '\0') {
    uVar2 = FUN_005c8250("abstor",1,"goal1b",0,0);
    *(undefined4 *)(param_1 + 0x3ec) = uVar2;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x3f0);
  if (cVar1 == '\0') {
    uVar2 = FUN_005c8250("abstor",2,"goal2a",0,0);
    *(undefined4 *)(param_1 + 0x3f0) = uVar2;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x3f4);
  if (cVar1 == '\0') {
    uVar2 = FUN_005c8250("abstor",2,"goal2b",0,0);
    *(undefined4 *)(param_1 + 0x3f4) = uVar2;
  }
  return;
}

