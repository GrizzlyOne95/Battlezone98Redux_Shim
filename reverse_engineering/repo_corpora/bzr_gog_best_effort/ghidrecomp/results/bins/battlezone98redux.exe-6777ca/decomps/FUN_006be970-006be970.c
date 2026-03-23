
/* WARNING: Removing unreachable block (ram,0x006beaa8) */

void __fastcall FUN_006be970(undefined1 *param_1)

{
  char cVar1;
  longlong lVar2;
  ulonglong uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  uint uStack_70;
  undefined1 local_60 [8];
  undefined1 local_58 [8];
  ulonglong local_50;
  undefined8 local_48;
  undefined1 local_40 [11];
  char local_35;
  undefined1 *local_34;
  undefined1 local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008516d1;
  local_10 = ExceptionList;
  uStack_70 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_70;
  ExceptionList = &local_10;
  local_8 = 0x13;
  *param_1 = 1;
  local_34 = param_1;
  local_18 = uStack_70;
  FUN_004fbb60();
  FUN_006cb0c0(local_40);
  FUN_006cb0c0(local_40);
  FUN_006cb0c0(local_40);
  FUN_006cb300(local_60,local_40);
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    FUN_0081e0c0("BZRNetInterface active_con closed due to bzr net interface shutdown\n");
    FUN_006ab750();
    basic_string<>("Program Exiting");
    local_8._0_1_ = 0x14;
    puVar6 = local_58;
    puVar5 = local_30;
    uVar4 = 0x3e9;
    FUN_00421ec0(0x3e9,puVar5,puVar6);
    FUN_006dacd0(uVar4,puVar5,puVar6);
    local_8 = CONCAT31(local_8._1_3_,0x13);
    ~basic_string<>();
  }
  local_8 = CONCAT31(local_8._1_3_,0x15);
  lVar2 = FUN_00822ea0();
  local_50 = lVar2 + 5000;
  do {
    local_35 = FUN_006ae200();
    if (local_35 != '\0') {
LAB_006beacc:
      FUN_006bead4();
      return;
    }
    uVar3 = FUN_00822ea0();
    local_48 = uVar3;
    if (local_50 < uVar3) {
      FUN_0081e0c0("BZRNetInterface shutdown took too long, trying brute force next\n");
      goto LAB_006beacc;
    }
    FUN_006ae1a0();
  } while( true );
}

