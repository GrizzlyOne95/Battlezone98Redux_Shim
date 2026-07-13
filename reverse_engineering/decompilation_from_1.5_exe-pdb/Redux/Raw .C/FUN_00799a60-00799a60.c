
void __fastcall FUN_00799a60(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_00764bb0(param_1);
  if (iVar1 == 1) {
    piVar2 = (int *)FUN_007647a0();
    (**(code **)(*piVar2 + 0xc))();
  }
  else {
    FUN_007c7930(0x1f);
  }
  return;
}

