
bool __thiscall FUN_004e9220(int *param_1,int param_2)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  
  cVar2 = (**(code **)(*param_1 + 0x60))(param_2);
  if (cVar2 == '\0') {
    FUN_004376c0(param_1[0x3e] + 0x160,param_1[0x3d],0);
  }
  else {
    iVar1 = param_1[0x3e];
    (**(code **)(*(int *)(param_2 + 0x18) + 0x28))(*(undefined4 *)(iVar1 + 0x170));
    uVar3 = (**(code **)(*(int *)(param_2 + 0x18) + 0x30))(0);
    FUN_004376c0(iVar1 + 0x150,uVar3);
    FUN_0062de40(param_1[0x3d],0x200);
  }
  return cVar2 != '\0';
}

