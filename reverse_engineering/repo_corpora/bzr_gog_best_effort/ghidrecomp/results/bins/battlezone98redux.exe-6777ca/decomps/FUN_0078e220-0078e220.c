
void __fastcall FUN_0078e220(int param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0078c4a0(uVar2);
  pvVar3 = operator_new(0x144);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007d1cc0("Splash_Overlay1",0,0,0,0,0x201,0,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x150) = local_1c;
  FUN_007d3f20(5);
  uVar4 = 1;
  puVar5 = PTR_s_BattleZone_Title_Screen_png_008f0680;
  FUN_007647a0(1,uVar2,local_1c,PTR_s_BattleZone_Title_Screen_png_008f0680);
  cVar1 = FUN_007537a0(uVar4);
  if (cVar1 != '\0') {
    puVar5 = PTR_s_Battlezone_TRO_png_008f067c;
  }
  FUN_007d2870(puVar5);
  FUN_007d2110();
  *(undefined4 *)(param_1 + 0x148) = 2;
  uVar4 = FUN_00822e60();
  *(undefined4 *)(param_1 + 0x14c) = uVar4;
  FUN_0078c4b0(0x4097700000000000,FUN_0078dfe0);
  ExceptionList = local_10;
  return;
}

