
void __fastcall FUN_005e1da0(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0xd8) = 0;
  iVar1 = FUN_00439e70();
  iVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0xcc) + 0x18) + 0x2c))();
  if (iVar1 == iVar2) {
    FUN_0049b430(0x3f800000,0x3f800000,0xff,0xff,0xff);
  }
  return;
}

