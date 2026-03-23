
void __fastcall FUN_0079cda0(int param_1)

{
  uint uVar1;
  longlong lVar2;
  
  FUN_007d37f0();
  (**(code **)**(undefined4 **)(param_1 + 0x1cc))();
  lVar2 = FUN_00822ea0();
  uVar1 = (uint)((ulonglong)lVar2 >> 0x20);
  if ((*(uint *)(param_1 + 0x14c) <= uVar1) &&
     ((uVar1 != *(uint *)(param_1 + 0x14c) || (*(uint *)(param_1 + 0x148) < (uint)lVar2)))) {
    *(longlong *)(param_1 + 0x148) = lVar2 + 15000;
    FUN_0073d860(1);
  }
  return;
}

