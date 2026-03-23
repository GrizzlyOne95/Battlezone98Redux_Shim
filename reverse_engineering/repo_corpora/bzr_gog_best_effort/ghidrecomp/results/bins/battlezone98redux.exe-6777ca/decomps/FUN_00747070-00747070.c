
undefined2 __fastcall FUN_00747070(int *param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_1c [20];
  int *local_8;
  
  local_8 = param_1;
  uVar2 = (**(code **)(*param_1 + 0x38))(local_1c);
  iVar3 = FUN_00746690(uVar2);
  if (iVar3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(iVar3 + 0x28);
  }
  return uVar1;
}

