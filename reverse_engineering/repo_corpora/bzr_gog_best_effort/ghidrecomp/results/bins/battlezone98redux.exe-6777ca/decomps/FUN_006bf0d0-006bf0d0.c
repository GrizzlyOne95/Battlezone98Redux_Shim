
void __fastcall FUN_006bf0d0(char *param_1)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  char *pcStack_48;
  undefined *puStack_44;
  uint uStack_40;
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined *local_18;
  char *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008517c0;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  param_1[9] = '\0';
  local_14 = param_1;
  if (*(int *)(param_1 + 0xc38) != 0) {
    puStack_44 = (undefined *)0x6bf120;
    FUN_0074d250();
  }
  if (*local_14 == '\0') {
    local_1c = (undefined1 *)&pcStack_48;
    local_20 = shared_ptr<>(&stack0x00000004);
    local_24 = FUN_006cbe40(local_2c);
    local_8 = CONCAT31(local_8._1_3_,1);
    puStack_44 = (undefined *)0x6bf169;
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      local_18 = &DAT_00873de0;
    }
    else {
      local_18 = &DAT_00873e10;
    }
    puStack_44 = local_18;
    pcStack_48 = (char *)0x6bf18c;
    FUN_00421ec0();
    pcStack_48 = (char *)0x6bf193;
    FUN_006cbfc0();
    pcStack_48 = (char *)0x6bf19a;
    pcStack_48 = (char *)FUN_0041f870();
    FUN_00421ec0();
    uVar2 = FUN_006cbfa0();
    FUN_00421ec0(uVar2);
    FUN_006cc000();
    uVar3 = FUN_0041f870();
    FUN_00421ec0(uVar3);
    uVar2 = FUN_006cbfe0();
    FUN_0081e0c0("BZRNetInterface reset active_con due to websocket connection close, remote %ld %s, local %ld %s, reset %s\n"
                 ,uVar2);
    puStack_44 = (undefined *)0x6bf1f3;
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
              ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_14 + 0x2e0));
    if (*(int *)(local_14 + 4) < 3) {
      local_14[4] = '\0';
      local_14[5] = '\0';
      local_14[6] = '\0';
      local_14[7] = '\0';
      puStack_44 = &DAT_0260b0a0;
      pcStack_48 = (char *)0x6bf216;
      FUN_006cb140();
      puStack_44 = (undefined *)(uint)*DAT_0260b098;
      pcStack_48 = local_14;
      puStack_44 = (undefined *)FUN_006db740(local_3c,FUN_006c35c0);
      pcStack_48 = (char *)0x6bf241;
      FUN_006db780();
    }
    else {
      local_14[4] = '\0';
      local_14[5] = '\0';
      local_14[6] = '\0';
      local_14[7] = '\0';
      puStack_44 = (undefined *)0x6bf255;
      FUN_004fbb60();
      puStack_44 = local_34;
      pcStack_48 = (char *)0x6bf261;
      FUN_006c35c0();
    }
    local_8 = local_8 & 0xffffff00;
    puStack_44 = (undefined *)0x6bf26d;
    FUN_006ca8c0();
  }
  else {
    local_14[4] = '\0';
    local_14[5] = '\0';
    local_14[6] = '\0';
    local_14[7] = '\0';
  }
  local_8 = 0xffffffff;
  puStack_44 = (undefined *)0x6bf288;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

