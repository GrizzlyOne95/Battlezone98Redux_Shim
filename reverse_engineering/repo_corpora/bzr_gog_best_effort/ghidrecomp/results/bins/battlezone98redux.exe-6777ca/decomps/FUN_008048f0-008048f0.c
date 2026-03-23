
bool __thiscall FUN_008048f0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000018;
  
  uVar2 = FUN_0066eeb0(&stack0x00000004,param_1);
  cVar1 = FUN_006dc8e0(uVar2);
  if (cVar1 == '\0') {
    FUN_007fe040(&stack0x00000004);
    FUN_00805700();
  }
  return cVar1 == '\0';
}

