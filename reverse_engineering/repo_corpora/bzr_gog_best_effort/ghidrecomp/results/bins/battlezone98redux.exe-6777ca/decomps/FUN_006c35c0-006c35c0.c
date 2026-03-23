
void FUN_006c35c0(void)

{
  char cVar1;
  char *pcStack_40;
  char *pcStack_3c;
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined4 local_c;
  char *local_8;
  
  pcStack_3c = (char *)0x6c35d1;
  cVar1 = FUN_004c85a0();
  if ((cVar1 != '\0') && (*local_8 == '\0')) {
    pcStack_3c = (char *)0x6c35f8;
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      if (local_8[0x2e8] != '\0') {
        pcStack_3c = (char *)0x6c361b;
        cVar1 = FUN_0041f890();
        if (cVar1 != '\0') {
          return;
        }
      }
      pcStack_3c = (char *)0x6c362f;
      FUN_006ab750();
      pcStack_3c = "BZRNetInterface starting connection to websocket\n";
      pcStack_40 = (char *)0x6c3639;
      FUN_0081e0c0();
      local_8[0x2d8] = '\0';
      local_8[0x2dc] = '\0';
      local_8[0x2dd] = '\0';
      local_8[0x2de] = '\0';
      local_8[0x2df] = '\0';
      pcStack_3c = local_20;
      pcStack_40 = local_8 + 0xc;
      pcStack_3c = (char *)FUN_006cb5b0(local_28);
      pcStack_40 = (char *)0x6c3685;
      local_c = pcStack_3c;
      FID_conflict_operator_();
      pcStack_3c = (char *)0x6c368d;
      FUN_006ca8c0();
      pcStack_3c = (char *)0x6c3695;
      cVar1 = FUN_006ab7d0();
      if (cVar1 == '\0') {
        local_10 = (undefined1 *)&pcStack_40;
        local_14 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                             ((shared_ptr<class___ExceptionPtr> *)&pcStack_40,
                              (shared_ptr<class___ExceptionPtr> *)(local_8 + 0x2e0));
        local_18 = FUN_006cb6a0(local_30);
        pcStack_3c = (char *)0x6c372a;
        FUN_006ca8c0();
      }
      else {
        pcStack_3c = (char *)0x6c36aa;
        std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                  ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_8 + 0x2e0));
        pcStack_3c = "BZRNetInterface reset active_con due to websocket initialization failed\n";
        pcStack_40 = (char *)0x6c36b4;
        FUN_0081e0c0();
        pcStack_3c = &DAT_0260b0a0;
        pcStack_40 = (char *)0x6c36c7;
        FUN_006cb140();
        pcStack_3c = (char *)(uint)*DAT_0260b098;
        pcStack_40 = local_8;
        pcStack_3c = (char *)FUN_006db740(local_38,FUN_006c35c0);
        pcStack_40 = (char *)0x6c36f2;
        FUN_006db780();
      }
    }
  }
  return;
}

