
void __fastcall FUN_00639760(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined1 *)(param_1 + 0x57) = 1;
  uVar1 = FUN_005c7e90("portal",0);
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    sprintf(local_18,"silo_attack%d",iVar2 + 1);
    uVar1 = FUN_005c7e90(local_18);
    *(undefined4 *)(param_1 + 0xa4 + iVar2 * 4) = uVar1;
    sprintf(local_18,"bdtank_%d",iVar2 + 1);
    uVar1 = FUN_005c7e90(local_18);
    *(undefined4 *)(param_1 + 0x7c + iVar2 * 4) = uVar1;
  }
  uVar1 = FUN_005c7e90("2bdest_1");
  *(undefined4 *)(param_1 + 0xcc) = uVar1;
  uVar1 = FUN_005c7e90("2bdest_2");
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  uVar1 = FUN_005c7e90("2bdest_3");
  *(undefined4 *)(param_1 + 0xd4) = uVar1;
  uVar1 = FUN_005c7e90("2bdest_7");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("2bdest_9");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("2bdest_10");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  *(undefined4 *)(param_1 + 0x114) = 0;
  FUN_0083e885();
  return;
}

