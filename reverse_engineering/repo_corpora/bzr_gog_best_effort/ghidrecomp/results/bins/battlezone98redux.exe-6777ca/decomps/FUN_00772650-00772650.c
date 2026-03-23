
void FUN_00772650(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  iterator *this;
  undefined4 uVar4;
  undefined4 *puVar5;
  iterator *piVar6;
  undefined1 local_e8 [8];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined1 local_c8 [180];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e03b;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=
                    ((iterator *)&param_1,(iterator *)&stack0x0000000c);
  if (bVar1) {
    local_d8 = param_1;
    local_d4 = param_2;
    while( true ) {
      piVar6 = (iterator *)&stack0x0000000c;
      this = (iterator *)FUN_00730810(piVar6,uVar3);
      bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=(this,piVar6);
      if (!bVar1) break;
      local_d0 = local_d8;
      local_cc = local_d4;
      uVar4 = FUN_00772160();
      uVar4 = FUN_00417780(uVar4);
      FUN_00753550(uVar4);
      local_8 = 0;
      uVar4 = FUN_00772160();
      cVar2 = FUN_00768120(local_c8,uVar4);
      if (cVar2 == '\0') {
        while( true ) {
          local_e0 = local_d0;
          local_dc = local_cc;
          FUN_00730830();
          uVar4 = FUN_00772160();
          cVar2 = FUN_00768120(local_c8,uVar4);
          if (cVar2 == '\0') break;
          uVar4 = FUN_00772160();
          uVar4 = FUN_00417780(uVar4);
          FUN_00772160(uVar4);
          FUN_007529c0(uVar4);
          local_d0 = local_e0;
          local_cc = local_dc;
        }
        uVar4 = FUN_00417780(local_c8);
        FUN_00772160(uVar4);
        FUN_007529c0(uVar4);
      }
      else {
        puVar5 = (undefined4 *)FUN_00730810();
        FUN_00773070(local_e8,param_1,param_2,local_d8,local_d4,*puVar5,puVar5[1]);
        uVar4 = FUN_00417780(local_c8);
        FUN_00772160(uVar4);
        FUN_007529c0(uVar4);
      }
      local_8 = 0xffffffff;
      FUN_00753670();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

