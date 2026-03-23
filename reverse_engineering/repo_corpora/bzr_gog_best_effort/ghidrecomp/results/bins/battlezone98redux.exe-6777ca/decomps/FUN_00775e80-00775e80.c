
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00775e80(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  float10 fVar4;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(&DAT_02c06678,0,0xd0);
  memset(&DAT_02c03f18,0,0x280);
  DAT_02c0667c = FUN_00787ac0(s_Clouds_008f0474,"Count",0,&DAT_02cc40c0);
  fVar4 = (float10)FUN_00787b60(s_Clouds_008f0474,"TileSize",0x42c80000,&DAT_02cc40c0);
  _DAT_02c06684 = (float)fVar4;
  DAT_02c06680 = FUN_00787ac0(s_Clouds_008f0474,&DAT_0089d14c,0,&DAT_02cc40c0);
  if (0.0 < _DAT_02c06684) {
    if (DAT_02c0667c < 1) {
      DAT_02c0667c = 0;
    }
    else {
      if (0x20 < DAT_02c0667c) {
        DAT_02c0667c = 0x20;
      }
      for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1) {
        sprintf(local_18,"Texture%d",local_1c);
        FUN_00787a30(s_Clouds_008f0474,local_18,&DAT_008a1ad8,&DAT_02c066c8 + DAT_02c06678 * 0x10,
                     0x10,&DAT_02cc40c0);
        sprintf(local_18,"Size%d",local_1c);
        fVar4 = (float10)FUN_00787b60(s_Clouds_008f0474,local_18,0x42c80000,&DAT_02cc40c0);
        *(float *)(&DAT_02c06688 + DAT_02c06678 * 4) = (float)fVar4;
        sprintf(local_18,"Height%d",local_1c);
        fVar4 = (float10)FUN_00787b60(s_Clouds_008f0474,local_18,0x42c80000,&DAT_02cc40c0);
        *(float *)(&DAT_02c066a8 + DAT_02c06678 * 4) = (float)fVar4 + (float)local_1c;
        if ((&DAT_02c066c8)[DAT_02c06678 * 0x10] != '\0') {
          DAT_02c06678 = DAT_02c06678 + 1;
        }
      }
      if (DAT_02c06678 < 1) {
        DAT_02c0667c = 0;
      }
      else {
        iVar1 = (int)_DAT_02c06684;
        if (iVar1 < 1) {
          DAT_02c0667c = 0;
        }
        else {
          for (local_1c = 0; local_1c < DAT_02c0667c; local_1c = local_1c + 1) {
            iVar2 = rand();
            iVar2 = iVar2 % DAT_02c06678;
            uVar3 = rand();
            uVar3 = uVar3 & 0x80000003;
            if ((int)uVar3 < 0) {
              uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
            }
            (&DAT_02c03f28)[local_1c * 5] = uVar3;
            (&DAT_02c03f24)[local_1c * 5] = iVar2;
            (&DAT_02c03f1c)[local_1c * 5] = *(undefined4 *)(&DAT_02c066a8 + iVar2 * 4);
            iVar2 = rand();
            (&DAT_02c03f18)[local_1c * 5] = (float)(iVar2 % iVar1);
            iVar2 = rand();
            (&DAT_02c03f20)[local_1c * 5] = (float)(iVar2 % iVar1);
          }
        }
      }
    }
  }
  else {
    DAT_02c0667c = 0;
  }
  FUN_0083e885();
  return;
}

