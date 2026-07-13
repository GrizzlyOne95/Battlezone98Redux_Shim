
void FUN_006bee20(void)

{
  char cVar1;
  undefined4 uVar2;
  CDHtmlElementEventSink *pCVar3;
  uint uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 local_74 [8];
  int local_6c;
  undefined1 local_68 [28];
  undefined1 local_4c [28];
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851748;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 == '\0') {
    local_8 = 0xffffffff;
    FUN_006c9420();
  }
  else {
    FUN_0081e820("Websocket established!\n");
    uVar2 = FUN_0081e660();
    FUN_004bc590(uVar2);
    puVar7 = local_68;
    puVar6 = local_4c;
    pCVar3 = (CDHtmlElementEventSink *)FUN_00421ec0(puVar6,puVar7);
    CDHtmlElementEventSink::~CDHtmlElementEventSink(pCVar3);
    FUN_006cacd0(puVar6);
    uVar2 = FUN_006cac80(puVar7);
    FUN_006cb500(uVar2);
    puVar7 = local_30;
    pCVar3 = (CDHtmlElementEventSink *)FUN_00421ec0(puVar7);
    CDHtmlElementEventSink::~CDHtmlElementEventSink(pCVar3);
    FUN_006cacd0(puVar7);
    uVar4 = FUN_006cac60();
    FUN_006cb4e0((uVar4 & 0xffff) + 1);
    *(undefined4 *)(local_6c + 4) = 1;
    uVar2 = FUN_006b2a40(1);
    iVar5 = FUN_006cb140(uVar2);
    if (iVar5 != 0) {
      FUN_004fbb60();
      FUN_006c6a10(local_74);
    }
    local_8 = 0xffffffff;
    FUN_006c9420();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

