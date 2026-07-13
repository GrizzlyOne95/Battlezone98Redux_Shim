
void __thiscall FUN_004aefa0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_00417dd0(param_1);
  if (cVar1 == '\0') {
    FUN_0046fa60(param_2,0,0);
  }
  else {
    cVar1 = FUN_004aef60();
    if (cVar1 == '\0') {
      FUN_0046fa60(param_2,0x18,1);
    }
    else {
      FUN_0046fa60(param_2,0x19,1);
    }
  }
  return;
}

