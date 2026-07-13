
void __thiscall FUN_00437fc0(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  void *local_18;
  undefined4 local_14;
  void *local_10;
  undefined4 local_c;
  int local_8;
  
  if (param_2 != 0) {
    local_8 = param_1;
    if (param_2 == *(int *)(param_1 + 0x3c)) {
      FUN_00438080(*(undefined4 *)(param_1 + 0x38));
    }
    else {
      FUN_0042d8c0(&local_c);
      while( true ) {
        uVar2 = FID_conflict_begin(local_20);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 == '\0') break;
        piVar3 = (int *)FUN_0042de50();
        local_10 = (void *)*piVar3;
        if (*(int *)((int)local_10 + 4) == param_2) {
          local_14 = local_c;
          FUN_0042d920(local_24,local_c);
          local_18 = local_10;
          operator_delete(local_10);
          return;
        }
        FUN_00438c10(local_1c,0);
      }
    }
  }
  return;
}

