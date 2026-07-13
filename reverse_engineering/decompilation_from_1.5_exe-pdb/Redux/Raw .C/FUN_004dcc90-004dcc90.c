
char FUN_004dcc90(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined4 local_30;
  undefined4 local_2c;
  void *local_28;
  int *local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a17c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_11 = '\x01';
  local_20 = DAT_00917a74;
  local_30 = FUN_0045ca50(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_24 = (int *)FUN_00417c70();
  FUN_007d6a70("Executing GameObject::PostLoadAll\n");
  FID_conflict_begin(local_1c);
  while( true ) {
    if (local_11 == '\0') {
      ExceptionList = local_10;
      return '\0';
    }
    uVar2 = FID_conflict_end(local_38);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    local_18 = (int *)FUN_00421ec0();
    local_18 = (int *)*local_18;
    if ((DAT_009173b7 != '\0') && (local_18[0x3f] != 0)) {
      local_18[0x3f] = 0;
      if (local_18 == local_24) {
        uVar2 = FUN_004978b0();
        FUN_007d6a70("UserProcess : %s\n",uVar2);
        local_28 = operator_new(200);
        local_8 = 0;
        if (local_28 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_00608d40(local_30,local_24);
        }
        local_8 = 0xffffffff;
      }
      else {
        uVar2 = FUN_004978b0();
        FUN_007d6a70("AiProcess : %s\n",uVar2);
        FUN_00461440(local_30,local_18);
      }
    }
    local_11 = (**(code **)(*local_18 + 0x58))();
    FUN_0046b260(local_34,0);
  }
  ExceptionList = local_10;
  return local_11;
}

