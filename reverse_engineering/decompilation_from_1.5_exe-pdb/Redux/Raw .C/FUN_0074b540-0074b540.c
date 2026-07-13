
void __thiscall FUN_0074b540(int param_1,byte param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  
  cVar1 = FUN_00742cf0(param_1);
  if (cVar1 != '\0') {
    if (param_2 == 0) {
      FUN_0081e820("Lobby ",param_1 + 0x28," unlocked\n");
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_0073ba70(uVar2);
      FUN_004bc590(uVar2);
    }
    else {
      FUN_0081e820("Lobby ",param_1 + 0x28," locked\n");
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_0073ba70(uVar2);
      FUN_004bc590(uVar2);
    }
    uVar3 = (uint)param_2;
    get(uVar3);
    FUN_006c5290(uVar3);
  }
  return;
}

