
void FUN_00774d40(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int local_64;
  int local_60;
  undefined1 local_58 [32];
  char local_38 [32];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(&DAT_02c00ef8,0,0x220);
  memset(&DAT_02c01118,0,0x2e00);
  DAT_008f049c = FUN_00787ac0("AnimatedScrounge",&DAT_0089d080,DAT_008f049c,&DAT_02cc40c0);
  DAT_008f0590 = FUN_00787ac0("AnimatedScrounge",&DAT_0089d064,DAT_008f0590,&DAT_02cc40c0);
  DAT_00945494 = FUN_00787ac0("AnimatedScrounge","Count",DAT_00945494,&DAT_02cc40c0);
  DAT_008f050c = FUN_00787ac0("AnimatedScrounge","Diameter",DAT_008f050c,&DAT_02cc40c0);
  if (DAT_008f050c < 1) {
    DAT_008f050c = 1;
  }
  if ((DAT_00945494 < 1) || (0x40 < DAT_00945494)) {
    DAT_00945494 = 0x20;
  }
  for (local_64 = 0; local_64 < 8; local_64 = local_64 + 1) {
    iVar2 = local_64 * 0x44;
    piVar3 = (int *)(&DAT_02c00ef8 + iVar2);
    sprintf(local_38,"AnimatedScroungeType%d",local_64);
    for (local_60 = 0; local_60 < 8; local_60 = local_60 + 1) {
      sprintf(local_18,"Name%d",local_60);
      FUN_00787a30(local_38,local_18,&DAT_008a1ad8,local_58,0x20,&DAT_02cc40c0);
      uVar1 = FUN_0068bed0(local_58);
      *(undefined4 *)(&DAT_02c00f1c + *piVar3 * 4 + iVar2) = uVar1;
      if (*(int *)(&DAT_02c00f1c + *piVar3 * 4 + iVar2) != 0) {
        sprintf(local_18,"Frames%d",local_60);
        uVar1 = FUN_00787ac0(local_38,local_18,0,&DAT_02cc40c0);
        *(undefined4 *)(&DAT_02c00efc + *piVar3 * 4 + iVar2) = uVar1;
        *piVar3 = *piVar3 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

