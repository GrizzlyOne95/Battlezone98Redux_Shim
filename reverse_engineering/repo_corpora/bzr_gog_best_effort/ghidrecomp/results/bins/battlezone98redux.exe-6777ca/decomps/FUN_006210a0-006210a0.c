
void FUN_006210a0(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int local_14;
  uint local_c;
  undefined2 local_8 [2];
  
  for (local_c = 0; (int)local_c < DAT_0091a430; local_c = local_c + 1) {
    iVar5 = local_c * 0x84;
    puVar1 = *(undefined4 **)(&DAT_00919918 + iVar5);
    if ((puVar1[0xb] == 0) || (*(char *)puVar1[0xb] == '\0')) {
      if ((puVar1[0xc] != 0) && (*(char *)puVar1[0xc] != '\0')) {
        bVar4 = *(byte *)(puVar1 + 5);
        iVar5 = *(int *)*puVar1;
        iVar2 = puVar1[3];
        iVar3 = puVar1[2];
        *(undefined4 *)puVar1[1] = 0;
        puVar1[7] = (int)((((double)(iVar5 << (bVar4 & 0x1f)) - (double)iVar2) * 2.0) /
                          (double)iVar3 - 65536.0);
      }
    }
    else {
      if (*(int *)(&DAT_0091990c + iVar5) != 0) {
        iVar2 = *(int *)(&DAT_00919904 + iVar5);
        if ((&DAT_0091a434)[iVar2] != 0) {
          (**(code **)((&DAT_0091fefc)[iVar2] + 0x10))
                    (*(undefined4 *)(&DAT_0091ff80 + iVar2 * 0x74),
                     *(undefined4 *)(&DAT_00919908 + iVar5));
        }
      }
      puVar1[7] = puVar1[4];
      *(undefined4 *)puVar1[1] = 0;
      *(undefined4 *)(&DAT_00919910 + iVar5) = 0;
    }
    *(undefined1 *)((int)puVar1 + 0x15) = 0;
  }
  for (local_c = 0; local_c < 0x6f; local_c = local_c + 1) {
    if (*(int *)(&DAT_008eb1f0 + local_c * 0x20) != 0) {
      *(&PTR_DAT_008eb1ec)[local_c * 8] = 0;
    }
  }
  if (DAT_009198f8 == 0) {
    for (local_c = 0; (int)local_c < DAT_0091a364; local_c = local_c + 1) {
      if (((&DAT_0091a434)[local_c] != 0) &&
         ((local_c != DAT_0091a44c || (iVar5 = FUN_00823ce0(), iVar5 == 0)))) {
        (**(code **)((&DAT_0091fefc)[local_c] + 0x14))
                  (*(undefined4 *)(&DAT_0091ff80 + local_c * 0x74),&DAT_02a142e0 + local_c * 0x50,
                   &DAT_02a14320 + local_c * 0x50);
      }
    }
    for (local_c = 0; (int)local_c < DAT_0091843c; local_c = local_c + 1) {
      if ((DAT_008ead6c != 0) || (*(int *)(&DAT_0091a468 + local_c * 0x74) != 0)) {
        bVar4 = FUN_0061efe0(*(undefined4 *)(&DAT_0091a464 + local_c * 0x74),
                             &DAT_0091a46c + local_c * 0x74);
        if (((&DAT_0091a460)[local_c * 0x74] == '\0') || ((&DAT_0091a461)[local_c * 0x74] == '\0'))
        {
          **(byte **)(&DAT_0091a45c + local_c * 0x74) =
               **(byte **)(&DAT_0091a45c + local_c * 0x74) | bVar4;
        }
        (&DAT_0091a461)[local_c * 0x74] = bVar4;
      }
    }
    for (local_c = 0; (int)local_c < DAT_0091a430; local_c = local_c + 1) {
      if ((DAT_008ead6c != 0) || (*(int *)(&DAT_00919980 + local_c * 0x84) != 0)) {
        iVar5 = FUN_00620d10(&DAT_00919900 + local_c * 0x84);
        if ((iVar5 == 0) && (*(int *)(&DAT_0091990c + local_c * 0x84) != 0)) {
          iVar5 = FUN_0061efe0(*(undefined4 *)(&DAT_0091991c + local_c * 0x84),
                               &DAT_00919920 + local_c * 0x84);
          if (iVar5 == 0) {
            local_14 = 0;
          }
          else {
            local_14 = **(int **)(&DAT_0091990c + local_c * 0x84) *
                       *(int *)(&DAT_00919914 + local_c * 0x84);
          }
          if (*(int *)(&DAT_00919910 + local_c * 0x84) == local_14) {
            if (*(int *)(&DAT_00919918 + local_c * 0x84) + 0x1c ==
                *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 4)) {
              *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 0x1c) = local_14;
            }
          }
          else {
            *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 0x1c) = local_14;
          }
          *(int *)(&DAT_00919910 + local_c * 0x84) = local_14;
        }
        local_14 = *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 0x1c);
        if (0x10000 < local_14) {
          local_14 = 0x10000;
        }
        if (local_14 < -0x10000) {
          local_14 = -0x10000;
        }
        *(int *)**(undefined4 **)(&DAT_00919918 + local_c * 0x84) =
             ((local_14 + 0x10000) * *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 8)) / 2 +
             *(int *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 0xc) >>
             (*(byte *)(*(int *)(&DAT_00919918 + local_c * 0x84) + 0x14) & 0x1f);
      }
    }
    iVar5 = FUN_004344a0();
    if (iVar5 == 2) {
      FUN_0041e750();
    }
  }
  else {
    FUN_00434f20();
  }
  if ((&DAT_0091a434)[DAT_0091a44c] == 0) {
    local_8[0] = 0;
  }
  else {
    (**(code **)((&DAT_0091fefc)[DAT_0091a44c] + 0x18))(local_8);
  }
  DAT_0091989c = local_8[0];
  return;
}

