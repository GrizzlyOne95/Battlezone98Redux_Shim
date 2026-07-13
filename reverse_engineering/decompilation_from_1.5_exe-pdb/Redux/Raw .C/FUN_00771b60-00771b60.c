
pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator> *
FUN_00771b60(pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator>
             *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            byte param_6)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  iterator *piVar7;
  iterator *piVar8;
  uint uVar9;
  undefined1 local_8c [8];
  undefined1 local_84 [8];
  undefined1 local_7c [8];
  undefined1 local_74 [8];
  undefined1 local_6c [8];
  undefined1 local_64 [8];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar3 = FUN_00732ef0(&param_2);
  FUN_00732eb0(&local_2c,iVar3 / 2);
  uVar9 = (uint)param_6;
  puVar4 = (undefined4 *)FUN_007721c0(local_54,1);
  FUN_00772860(param_2,param_3,local_2c,local_28,*puVar4,puVar4[1],uVar9);
  local_c = local_2c;
  local_8 = local_28;
  FUN_00732eb0(&local_14,1);
  while (bVar1 = __FrameHandler3::TryBlockMap::iterator::operator<
                           ((iterator *)&param_2,(iterator *)&local_c), bVar1) {
    uVar5 = FUN_00772230();
    FUN_007721c0(local_44,1);
    uVar6 = FUN_00772230(uVar5);
    cVar2 = FUN_007681a0(uVar6,uVar5);
    if (cVar2 != '\0') break;
    FUN_007721c0(local_84,1);
    uVar5 = FUN_00772230();
    uVar6 = FUN_00772230(uVar5);
    cVar2 = FUN_007681a0(uVar6,uVar5);
    if (cVar2 != '\0') break;
    FUN_00730830();
  }
  do {
    bVar1 = __FrameHandler3::TryBlockMap::iterator::operator<
                      ((iterator *)&local_14,(iterator *)&param_4);
    if (!bVar1) break;
    uVar5 = FUN_00772230();
    uVar6 = FUN_00772230(uVar5);
    cVar2 = FUN_007681a0(uVar6,uVar5);
    if (cVar2 != '\0') break;
    uVar5 = FUN_00772230();
    uVar6 = FUN_00772230(uVar5);
    cVar2 = FUN_007681a0(uVar6,uVar5);
    if (cVar2 != '\0') break;
    FUN_00730810();
  } while( true );
  local_24 = local_14;
  local_20 = local_10;
  local_1c = local_c;
  local_18 = local_8;
  do {
    while (bVar1 = __FrameHandler3::TryBlockMap::iterator::operator<
                             ((iterator *)&local_24,(iterator *)&param_4), !bVar1) {
LAB_00771d80:
      while (bVar1 = __FrameHandler3::TryBlockMap::iterator::operator<
                               ((iterator *)&param_2,(iterator *)&local_1c), bVar1) {
        uVar5 = FUN_00772230();
        FUN_007721c0(local_64,1);
        uVar6 = FUN_00772230(uVar5);
        cVar2 = FUN_007681a0(uVar6,uVar5);
        if (cVar2 == '\0') {
          FUN_007721c0(local_3c,1);
          uVar5 = FUN_00772230();
          uVar6 = FUN_00772230(uVar5);
          cVar2 = FUN_007681a0(uVar6,uVar5);
          if (cVar2 != '\0') break;
          piVar7 = (iterator *)FUN_007721c0(local_4c,1);
          piVar8 = (iterator *)FUN_00730830();
          bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=(piVar8,piVar7);
          if (bVar1) {
            puVar4 = (undefined4 *)FUN_007721c0(local_5c,1);
            FUN_007729e0(local_c,local_8,*puVar4,puVar4[1]);
          }
        }
        FUN_00730830();
      }
      bVar1 = __FrameHandler3::HandlerMap::iterator::operator==
                        ((iterator *)&local_1c,(iterator *)&param_2);
      if ((bVar1) &&
         (bVar1 = __FrameHandler3::HandlerMap::iterator::operator==
                            ((iterator *)&local_24,(iterator *)&param_4), bVar1)) {
        std::
        pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator>
        ::
        pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator><class___FrameHandler3::TryBlockMap::iterator&,class___FrameHandler3::TryBlockMap::iterator&,0>
                  (param_1,(iterator *)&local_c,(iterator *)&local_14);
        return param_1;
      }
      bVar1 = __FrameHandler3::HandlerMap::iterator::operator==
                        ((iterator *)&local_1c,(iterator *)&param_2);
      if (bVar1) {
        bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=
                          ((iterator *)&local_14,(iterator *)&local_24);
        if (bVar1) {
          FUN_007729e0(local_c,local_8,local_14,local_10);
        }
        FUN_00730810();
        puVar4 = (undefined4 *)FUN_00772180(local_6c,0);
        uVar5 = puVar4[1];
        uVar6 = *puVar4;
        puVar4 = (undefined4 *)FUN_00772180(local_7c,0);
        FUN_007729e0(*puVar4,puVar4[1],uVar6,uVar5);
      }
      else {
        bVar1 = __FrameHandler3::HandlerMap::iterator::operator==
                          ((iterator *)&local_24,(iterator *)&param_4);
        if (bVar1) {
          piVar7 = (iterator *)FUN_00730830();
          piVar8 = (iterator *)FUN_00730830();
          bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=(piVar8,piVar7);
          if (bVar1) {
            FUN_007729e0(local_1c,local_18,local_c,local_8);
          }
          puVar4 = (undefined4 *)FUN_00730830();
          FUN_007729e0(local_c,local_8,*puVar4,puVar4[1]);
        }
        else {
          puVar4 = (undefined4 *)FUN_00730830();
          uVar5 = puVar4[1];
          uVar6 = *puVar4;
          puVar4 = (undefined4 *)FUN_00772180(local_8c,0);
          FUN_007729e0(*puVar4,puVar4[1],uVar6,uVar5);
        }
      }
    }
    uVar5 = FUN_00772230();
    uVar6 = FUN_00772230(uVar5);
    cVar2 = FUN_007681a0(uVar6,uVar5);
    if (cVar2 == '\0') {
      uVar5 = FUN_00772230();
      uVar6 = FUN_00772230(uVar5);
      cVar2 = FUN_007681a0(uVar6,uVar5);
      if (cVar2 != '\0') goto LAB_00771d80;
      piVar7 = (iterator *)&local_24;
      piVar8 = (iterator *)FUN_00772180(local_34,0);
      bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=(piVar8,piVar7);
      if (bVar1) {
        uVar5 = local_24;
        uVar6 = local_20;
        puVar4 = (undefined4 *)FUN_007721c0(local_74,1);
        FUN_007729e0(*puVar4,puVar4[1],uVar5,uVar6);
      }
    }
    FUN_00730810();
  } while( true );
}

