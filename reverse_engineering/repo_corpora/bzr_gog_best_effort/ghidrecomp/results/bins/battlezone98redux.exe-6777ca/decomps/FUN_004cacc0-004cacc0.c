
void __fastcall FUN_004cacc0(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  
  while( true ) {
    cVar1 = FUN_0042d8f0(param_1);
    if (cVar1 != '\0') break;
    puVar2 = (undefined4 *)FUN_0045e220();
    param_1 = (int *)*puVar2;
    (**(code **)(*param_1 + 0xc))();
  }
  return;
}

