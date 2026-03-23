
void __fastcall FUN_00588d70(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_0058a140(param_1);
  if (cVar1 == '\0') {
    uVar2 = FUN_004505c0();
    FUN_007d6b70("%d ParameterDB entries still open\n",uVar2);
  }
  FUN_004bb060();
  return;
}

