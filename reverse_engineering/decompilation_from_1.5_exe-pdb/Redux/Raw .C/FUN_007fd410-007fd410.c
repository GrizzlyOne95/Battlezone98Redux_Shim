
void FUN_007fd410(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  do {
    cVar1 = FID_conflict_operator__(param_2);
    if (cVar1 == '\0') {
      return;
    }
    cVar1 = FUN_007feb50(param_1,param_2,&DAT_0260c0e5,&DAT_0260c0e5,&DAT_0260c0e5);
  } while (cVar1 != '\0');
  return;
}

