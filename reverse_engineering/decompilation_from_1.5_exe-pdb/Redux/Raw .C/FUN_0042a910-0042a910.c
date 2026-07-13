
void __thiscall FUN_0042a910(uint *param_1,uint param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  void *local_10;
  undefined4 local_c;
  uint *local_8;
  
  if ((param_2 < *param_1) || (*param_1 + param_1[1] <= param_2)) {
    local_8 = param_1;
    FUN_0042d8c0(&local_c);
    while( true ) {
      uVar2 = FID_conflict_begin(local_18);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (uint *)FUN_0042da60();
      if (param_2 == *puVar3) {
        puVar4 = (undefined4 *)FUN_0042da60();
        local_10 = (void *)*puVar4;
        operator_delete__(local_10);
        local_14 = local_c;
        FUN_0042d920(local_1c,local_c);
        return;
      }
      FUN_0042da80();
    }
  }
  return;
}

