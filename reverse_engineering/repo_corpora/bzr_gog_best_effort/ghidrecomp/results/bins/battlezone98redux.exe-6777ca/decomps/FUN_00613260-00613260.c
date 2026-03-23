
bool __thiscall FUN_00613260(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_006131e0(param_2,*(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x170));
  if (cVar1 == '\0') {
    FUN_004376c0(*(int *)(param_1 + 0xf8) + 0x160,*(undefined4 *)(param_1 + 0xf4),0);
  }
  else {
    uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 0x30))(0);
    FUN_004376c0(*(int *)(param_1 + 0xf8) + 0x150,uVar2);
    FUN_0062de40(*(undefined4 *)(param_1 + 0xf4),0x200);
  }
  return cVar1 != '\0';
}

