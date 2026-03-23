
void FUN_0059c500(void)

{
  float *pfVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  char *_Str2;
  int iVar5;
  uint uVar6;
  float10 fVar7;
  size_t _MaxCount;
  undefined1 local_24 [4];
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined1 local_14 [4];
  int local_10;
  int local_c;
  int local_8;
  
  cVar2 = FUN_00571c40();
  if ((cVar2 == '\0') || (cVar2 = FUN_00571c30(), cVar2 != '\0')) {
    if (*(int *)(local_8 + 0x18) == 0) {
      *(undefined4 *)(local_8 + 0x18) = 1;
      for (local_10 = 0; local_10 < *(int *)(local_8 + 0x114c); local_10 = local_10 + 1) {
        FID_conflict_begin(local_14);
        while( true ) {
          uVar3 = FID_conflict_end(local_24);
          cVar2 = FID_conflict_operator__(uVar3);
          if (cVar2 == '\0') break;
          puVar4 = (undefined4 *)FUN_00421ec0();
          local_18 = *puVar4;
          _MaxCount = 0x14;
          _Str2 = (char *)FUN_004623e0();
          iVar5 = strncmp((char *)(local_8 + 0x28 + local_10 * 0x2c),_Str2,_MaxCount);
          if ((iVar5 == 0) && (uVar6 = FUN_0045c4b0(), (uVar6 & 0x200) == 0)) {
            uVar3 = FUN_00462380();
            *(undefined4 *)(local_8 + 0x1c + local_10 * 0x2c) = uVar3;
            break;
          }
          FUN_00421ee0();
        }
        if (*(int *)(local_8 + 0x1c + local_10 * 0x2c) == 0) {
          uVar3 = FUN_005c8250(local_8 + 0x3c + local_10 * 0x2c,0,local_8 + 0x28 + local_10 * 0x2c,0
                               ,local_8 + 0x28 + local_10 * 0x2c);
          *(undefined4 *)(local_8 + 0x1c + local_10 * 0x2c) = uVar3;
        }
        *(undefined1 *)(local_8 + 0x46 + local_10 * 0x2c) = 0;
      }
    }
    else {
      for (local_c = 0; local_c < *(int *)(local_8 + 0x114c); local_c = local_c + 1) {
        iVar5 = FUN_00462630(*(undefined4 *)(local_8 + 0x1c + local_c * 0x2c));
        if ((iVar5 == 0) && (*(char *)(local_8 + 0x46 + local_c * 0x2c) == '\0')) {
          *(undefined1 *)(local_8 + 0x46 + local_c * 0x2c) = 1;
          fVar7 = (float10)FUN_00822d80();
          local_1c = (float)fVar7;
          *(float *)(local_8 + 0x20 + local_c * 0x2c) =
               local_1c + *(float *)(local_8 + 0x24 + local_c * 0x2c);
        }
        if (*(char *)(local_8 + 0x46 + local_c * 0x2c) != '\0') {
          fVar7 = (float10)FUN_00822d80();
          local_20 = (float)fVar7;
          pfVar1 = (float *)(local_8 + 0x20 + local_c * 0x2c);
          if (*pfVar1 <= local_20 && local_20 != *pfVar1) {
            uVar3 = FUN_005c8250(local_8 + 0x3c + local_c * 0x2c,0,local_8 + 0x28 + local_c * 0x2c,0
                                 ,local_8 + 0x28 + local_c * 0x2c);
            *(undefined4 *)(local_8 + 0x1c + local_c * 0x2c) = uVar3;
            FUN_00462630(*(undefined4 *)(local_8 + 0x1c + local_c * 0x2c));
            *(undefined1 *)(local_8 + 0x46 + local_c * 0x2c) = 0;
          }
        }
      }
    }
  }
  return;
}

