
uint __thiscall FUN_0049cd50(int param_1,int param_2)

{
  uint in_EAX;
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    uVar2 = in_EAX & 0xffffff00;
  }
  else {
    uVar1 = FUN_00462380();
    *(undefined4 *)(param_1 + 0x3bc) = uVar1;
    uVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
    *(undefined4 *)(param_1 + 0x370) = uVar1;
    *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(*(int *)(param_1 + 0x370) + 0x54);
    uVar2 = CONCAT31((int3)((uint)*(int *)(param_1 + 0x370) >> 8),1);
  }
  return uVar2;
}

