
void __fastcall FUN_004f55b0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int *local_14;
  int *local_10;
  int *local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(char *)(param_1 + 0x2c) == '\0') {
    FUN_005cadd0(1,5);
    FUN_005cadd0(2,0x28);
    FUN_005cb2d0("inst01.aip",2);
    uVar1 = FUN_005c7e90("apdrop196_camerapod");
    *(undefined4 *)(local_8 + 0x1c) = uVar1;
    uVar1 = FUN_005c7e90("apcamr-1_camerapod");
    *(undefined4 *)(local_8 + 0x20) = uVar1;
    uVar1 = FUN_005c7e90("player-1_hover");
    *(undefined4 *)(local_8 + 0x24) = uVar1;
    uVar1 = FUN_005c7e90("eggeizr139_geyser");
    *(undefined4 *)(local_8 + 0x28) = uVar1;
    uVar1 = FUN_00460fc0("camera1");
    *(undefined4 *)(local_8 + 0x18) = uVar1;
    *(undefined1 *)(local_8 + 0x2c) = 1;
    *(undefined1 *)(local_8 + 0x2d) = 1;
    if (*(char *)(local_8 + 0x2d) != '\0') {
      FUN_00821e30();
    }
  }
  if (*(char *)(local_8 + 0x2d) != '\0') {
    local_20 = 0xdac;
    iVar2 = FUN_00462630(*(undefined4 *)(local_8 + 0x24));
    local_c = (int *)(iVar2 + 0x18);
    local_18 = (**(code **)(*local_c + 0x30))();
    local_1c = 500;
    FUN_00821fd0(*(undefined4 *)(local_8 + 0x18),&local_20,&local_1c,local_18);
    iVar2 = FUN_00821fb0();
    if (iVar2 != 0) {
      *(undefined1 *)(local_8 + 0x2d) = 0;
      uVar1 = FUN_00460fc0("camera2");
      *(undefined4 *)(local_8 + 0x18) = uVar1;
      *(undefined1 *)(local_8 + 0x2e) = 1;
    }
  }
  if (*(char *)(local_8 + 0x2e) != '\0') {
    local_2c = 0xdac;
    iVar2 = FUN_00462630(*(undefined4 *)(local_8 + 0x1c));
    local_10 = (int *)(iVar2 + 0x18);
    uVar1 = (**(code **)(*local_10 + 0x30))();
    iVar2 = FUN_00462630(*(undefined4 *)(local_8 + 0x28));
    local_14 = (int *)(iVar2 + 0x18);
    local_24 = (**(code **)(*local_14 + 0x30))();
    local_28 = 5000;
    FUN_00821fd0(*(undefined4 *)(local_8 + 0x18),&local_2c,&local_28,local_24,0,100,0,uVar1);
    iVar2 = FUN_00821fb0();
    if (iVar2 != 0) {
      *(undefined1 *)(local_8 + 0x2e) = 0;
      FUN_00821ec0();
    }
  }
  return;
}

