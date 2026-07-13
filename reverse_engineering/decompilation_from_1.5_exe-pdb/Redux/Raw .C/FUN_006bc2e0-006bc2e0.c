
/* WARNING: Removing unreachable block (ram,0x006bc36c) */
/* WARNING: Removing unreachable block (ram,0x006bc393) */
/* WARNING: Removing unreachable block (ram,0x006bc381) */

void FUN_006bc2e0(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  int *local_60;
  int local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 8);
  uVar2 = *(uint *)(param_1 + 0xc);
  uVar5 = *(uint *)(param_1 + 0x10);
  uVar4 = *(uint *)(param_1 + 0x14);
  if (((uint)param_2 & 3) == 0) {
    local_60 = param_2;
  }
  else {
    piVar10 = local_48;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar10 = *param_2;
      param_2 = param_2 + 1;
      piVar10 = piVar10 + 1;
    }
    local_60 = local_48;
  }
  uVar3 = (uVar2 & uVar5 | ~uVar2 & uVar4) + iVar1 + -0x28955b88 + *local_60;
  uVar3 = (uVar3 * 0x80 | uVar3 >> 0x19) + uVar2;
  uVar4 = (uVar3 & uVar2 | ~uVar3 & uVar5) + uVar4 + -0x173848aa + local_60[1];
  uVar4 = (uVar4 * 0x1000 | uVar4 >> 0x14) + uVar3;
  uVar5 = (uVar4 & uVar3 | ~uVar4 & uVar2) + uVar5 + 0x242070db + local_60[2];
  uVar5 = (uVar5 * 0x20000 | uVar5 >> 0xf) + uVar4;
  uVar2 = (uVar5 & uVar4 | ~uVar5 & uVar3) + uVar2 + -0x3e423112 + local_60[3];
  uVar7 = (uVar2 * 0x400000 | uVar2 >> 10) + uVar5;
  uVar2 = (uVar7 & uVar5 | ~uVar7 & uVar4) + uVar3 + -0xa83f051 + local_60[4];
  uVar3 = (uVar2 * 0x80 | uVar2 >> 0x19) + uVar7;
  uVar2 = (uVar3 & uVar7 | ~uVar3 & uVar5) + uVar4 + 0x4787c62a + local_60[5];
  uVar4 = (uVar2 * 0x1000 | uVar2 >> 0x14) + uVar3;
  uVar2 = (uVar4 & uVar3 | ~uVar4 & uVar7) + uVar5 + -0x57cfb9ed + local_60[6];
  uVar5 = (uVar2 * 0x20000 | uVar2 >> 0xf) + uVar4;
  uVar2 = (uVar5 & uVar4 | ~uVar5 & uVar3) + uVar7 + -0x2b96aff + local_60[7];
  uVar7 = (uVar2 * 0x400000 | uVar2 >> 10) + uVar5;
  uVar2 = (uVar7 & uVar5 | ~uVar7 & uVar4) + uVar3 + 0x698098d8 + local_60[8];
  uVar3 = (uVar2 * 0x80 | uVar2 >> 0x19) + uVar7;
  uVar2 = (uVar3 & uVar7 | ~uVar3 & uVar5) + uVar4 + -0x74bb0851 + local_60[9];
  uVar4 = (uVar2 * 0x1000 | uVar2 >> 0x14) + uVar3;
  uVar2 = (uVar4 & uVar3 | ~uVar4 & uVar7) + uVar5 + -0xa44f + local_60[10];
  uVar5 = (uVar2 * 0x20000 | uVar2 >> 0xf) + uVar4;
  uVar2 = (uVar5 & uVar4 | ~uVar5 & uVar3) + uVar7 + -0x76a32842 + local_60[0xb];
  uVar7 = (uVar2 * 0x400000 | uVar2 >> 10) + uVar5;
  uVar2 = (uVar7 & uVar5 | ~uVar7 & uVar4) + uVar3 + 0x6b901122 + local_60[0xc];
  uVar3 = (uVar2 * 0x80 | uVar2 >> 0x19) + uVar7;
  uVar2 = (uVar3 & uVar7 | ~uVar3 & uVar5) + uVar4 + -0x2678e6d + local_60[0xd];
  uVar4 = (uVar2 * 0x1000 | uVar2 >> 0x14) + uVar3;
  uVar2 = (uVar4 & uVar3 | ~uVar4 & uVar7) + uVar5 + -0x5986bc72 + local_60[0xe];
  uVar8 = (uVar2 * 0x20000 | uVar2 >> 0xf) + uVar4;
  uVar2 = (uVar8 & uVar4 | ~uVar8 & uVar3) + uVar7 + 0x49b40821 + local_60[0xf];
  uVar7 = (uVar2 * 0x400000 | uVar2 >> 10) + uVar8;
  uVar2 = (uVar7 & uVar4 | ~uVar4 & uVar8) + uVar3 + -0x9e1da9e + local_60[1];
  uVar3 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar7;
  uVar2 = (uVar3 & uVar8 | ~uVar8 & uVar7) + uVar4 + -0x3fbf4cc0 + local_60[6];
  uVar5 = (uVar2 * 0x200 | uVar2 >> 0x17) + uVar3;
  uVar2 = (uVar5 & uVar7 | ~uVar7 & uVar3) + uVar8 + 0x265e5a51 + local_60[0xb];
  uVar8 = (uVar2 * 0x4000 | uVar2 >> 0x12) + uVar5;
  uVar2 = (uVar8 & uVar3 | ~uVar3 & uVar5) + uVar7 + -0x16493856 + *local_60;
  uVar7 = (uVar2 * 0x100000 | uVar2 >> 0xc) + uVar8;
  uVar2 = (uVar7 & uVar5 | ~uVar5 & uVar8) + uVar3 + -0x29d0efa3 + local_60[5];
  uVar4 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar7;
  uVar9 = ((int)(&DAT_02441453 + local_60[10] + (uVar4 & uVar8 | ~uVar8 & uVar7) + uVar5) * 0x200 |
          (uint)(&DAT_02441453 + local_60[10] + (uVar4 & uVar8 | ~uVar8 & uVar7) + uVar5) >> 0x17) +
          uVar4;
  uVar2 = (uVar9 & uVar7 | ~uVar7 & uVar4) + uVar8 + -0x275e197f + local_60[0xf];
  uVar3 = (uVar2 * 0x4000 | uVar2 >> 0x12) + uVar9;
  uVar2 = (uVar3 & uVar4 | ~uVar4 & uVar9) + uVar7 + -0x182c0438 + local_60[4];
  uVar7 = (uVar2 * 0x100000 | uVar2 >> 0xc) + uVar3;
  uVar2 = (uVar7 & uVar9 | ~uVar9 & uVar3) + uVar4 + 0x21e1cde6 + local_60[9];
  uVar5 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar7;
  uVar2 = (uVar5 & uVar3 | ~uVar3 & uVar7) + uVar9 + -0x3cc8f82a + local_60[0xe];
  uVar4 = (uVar2 * 0x200 | uVar2 >> 0x17) + uVar5;
  uVar2 = (uVar4 & uVar7 | ~uVar7 & uVar5) + uVar3 + -0xb2af279 + local_60[3];
  uVar3 = (uVar2 * 0x4000 | uVar2 >> 0x12) + uVar4;
  uVar2 = (uVar3 & uVar5 | ~uVar5 & uVar4) + uVar7 + 0x455a14ed + local_60[8];
  uVar7 = (uVar2 * 0x100000 | uVar2 >> 0xc) + uVar3;
  uVar2 = (uVar7 & uVar4 | ~uVar4 & uVar3) + uVar5 + -0x561c16fb + local_60[0xd];
  uVar5 = (uVar2 * 0x20 | uVar2 >> 0x1b) + uVar7;
  uVar2 = (uVar5 & uVar3 | ~uVar3 & uVar7) + uVar4 + -0x3105c08 + local_60[2];
  uVar4 = (uVar2 * 0x200 | uVar2 >> 0x17) + uVar5;
  uVar2 = (uVar4 & uVar7 | ~uVar7 & uVar5) + uVar3 + 0x676f02d9 + local_60[7];
  uVar8 = (uVar2 * 0x4000 | uVar2 >> 0x12) + uVar4;
  uVar2 = (uVar8 & uVar5 | ~uVar5 & uVar4) + uVar7 + -0x72d5b376 + local_60[0xc];
  uVar3 = (uVar2 * 0x100000 | uVar2 >> 0xc) + uVar8;
  uVar2 = (uVar3 ^ uVar8 ^ uVar4) + uVar5 + -0x5c6be + local_60[5];
  uVar7 = (uVar2 * 0x10 | uVar2 >> 0x1c) + uVar3;
  uVar2 = (uVar7 ^ uVar3 ^ uVar8) + uVar4 + -0x788e097f + local_60[8];
  uVar5 = (uVar2 * 0x800 | uVar2 >> 0x15) + uVar7;
  uVar2 = (uVar5 ^ uVar7 ^ uVar3) + uVar8 + 0x6d9d6122 + local_60[0xb];
  uVar4 = (uVar2 * 0x10000 | uVar2 >> 0x10) + uVar5;
  uVar2 = (uVar4 ^ uVar5 ^ uVar7) + uVar3 + -0x21ac7f4 + local_60[0xe];
  uVar3 = (uVar2 * 0x800000 | uVar2 >> 9) + uVar4;
  uVar2 = (uVar3 ^ uVar4 ^ uVar5) + uVar7 + -0x5b4115bc + local_60[1];
  uVar7 = (uVar2 * 0x10 | uVar2 >> 0x1c) + uVar3;
  uVar2 = (uVar7 ^ uVar3 ^ uVar4) + uVar5 + 0x4bdecfa9 + local_60[4];
  uVar5 = (uVar2 * 0x800 | uVar2 >> 0x15) + uVar7;
  uVar2 = (uVar5 ^ uVar7 ^ uVar3) + uVar4 + -0x944b4a0 + local_60[7];
  uVar4 = (uVar2 * 0x10000 | uVar2 >> 0x10) + uVar5;
  uVar2 = (uVar4 ^ uVar5 ^ uVar7) + uVar3 + -0x41404390 + local_60[10];
  uVar3 = (uVar2 * 0x800000 | uVar2 >> 9) + uVar4;
  uVar2 = (uVar3 ^ uVar4 ^ uVar5) + uVar7 + 0x289b7ec6 + local_60[0xd];
  uVar7 = (uVar2 * 0x10 | uVar2 >> 0x1c) + uVar3;
  uVar2 = (uVar7 ^ uVar3 ^ uVar4) + uVar5 + -0x155ed806 + *local_60;
  uVar5 = (uVar2 * 0x800 | uVar2 >> 0x15) + uVar7;
  uVar2 = (uVar5 ^ uVar7 ^ uVar3) + uVar4 + -0x2b10cf7b + local_60[3];
  uVar4 = (uVar2 * 0x10000 | uVar2 >> 0x10) + uVar5;
  uVar2 = (uVar4 ^ uVar5 ^ uVar7) + uVar3 + 0x4881d05 + local_60[6];
  uVar3 = (uVar2 * 0x800000 | uVar2 >> 9) + uVar4;
  uVar2 = (uVar3 ^ uVar4 ^ uVar5) + uVar7 + -0x262b2fc7 + local_60[9];
  uVar7 = (uVar2 * 0x10 | uVar2 >> 0x1c) + uVar3;
  uVar2 = (uVar7 ^ uVar3 ^ uVar4) + uVar5 + -0x1924661b + local_60[0xc];
  uVar8 = (uVar2 * 0x800 | uVar2 >> 0x15) + uVar7;
  uVar2 = (uVar8 ^ uVar7 ^ uVar3) + uVar4 + 0x1fa27cf8 + local_60[0xf];
  uVar9 = (uVar2 * 0x10000 | uVar2 >> 0x10) + uVar8;
  uVar2 = (uVar9 ^ uVar8 ^ uVar7) + uVar3 + -0x3b53a99b + local_60[2];
  uVar5 = (uVar2 * 0x800000 | uVar2 >> 9) + uVar9;
  uVar2 = ((~uVar8 | uVar5) ^ uVar9) + uVar7 + -0xbd6ddbc + *local_60;
  uVar4 = (uVar2 * 0x40 | uVar2 >> 0x1a) + uVar5;
  uVar2 = ((~uVar9 | uVar4) ^ uVar5) + uVar8 + 0x432aff97 + local_60[7];
  uVar3 = (uVar2 * 0x400 | uVar2 >> 0x16) + uVar4;
  uVar2 = ((~uVar5 | uVar3) ^ uVar4) + uVar9 + -0x546bdc59 + local_60[0xe];
  uVar7 = (uVar2 * 0x8000 | uVar2 >> 0x11) + uVar3;
  uVar2 = ((~uVar4 | uVar7) ^ uVar3) + uVar5 + -0x36c5fc7 + local_60[5];
  uVar5 = (uVar2 * 0x200000 | uVar2 >> 0xb) + uVar7;
  uVar2 = ((~uVar3 | uVar5) ^ uVar7) + uVar4 + 0x655b59c3 + local_60[0xc];
  uVar4 = (uVar2 * 0x40 | uVar2 >> 0x1a) + uVar5;
  uVar2 = ((~uVar7 | uVar4) ^ uVar5) + uVar3 + -0x70f3336e + local_60[3];
  uVar3 = (uVar2 * 0x400 | uVar2 >> 0x16) + uVar4;
  uVar2 = ((~uVar5 | uVar3) ^ uVar4) + uVar7 + -0x100b83 + local_60[10];
  uVar7 = (uVar2 * 0x8000 | uVar2 >> 0x11) + uVar3;
  uVar2 = ((~uVar4 | uVar7) ^ uVar3) + uVar5 + -0x7a7ba22f + local_60[1];
  uVar8 = (uVar2 * 0x200000 | uVar2 >> 0xb) + uVar7;
  uVar2 = ((~uVar3 | uVar8) ^ uVar7) + uVar4 + 0x6fa87e4f + local_60[8];
  uVar5 = (uVar2 * 0x40 | uVar2 >> 0x1a) + uVar8;
  uVar2 = ((~uVar7 | uVar5) ^ uVar8) + uVar3 + -0x1d31920 + local_60[0xf];
  uVar4 = (uVar2 * 0x400 | uVar2 >> 0x16) + uVar5;
  uVar2 = ((~uVar8 | uVar4) ^ uVar5) + uVar7 + -0x5cfebcec + local_60[6];
  uVar3 = (uVar2 * 0x8000 | uVar2 >> 0x11) + uVar4;
  uVar2 = ((~uVar5 | uVar3) ^ uVar4) + uVar8 + 0x4e0811a1 + local_60[0xd];
  uVar7 = (uVar2 * 0x200000 | uVar2 >> 0xb) + uVar3;
  uVar2 = ((~uVar4 | uVar7) ^ uVar3) + uVar5 + -0x8ac817e + local_60[4];
  uVar5 = (uVar2 * 0x40 | uVar2 >> 0x1a) + uVar7;
  uVar2 = ((~uVar3 | uVar5) ^ uVar7) + uVar4 + -0x42c50dcb + local_60[0xb];
  uVar4 = (uVar2 * 0x400 | uVar2 >> 0x16) + uVar5;
  uVar2 = ((~uVar7 | uVar4) ^ uVar5) + uVar3 + 0x2ad7d2bb + local_60[2];
  uVar3 = (uVar2 * 0x8000 | uVar2 >> 0x11) + uVar4;
  uVar2 = ((~uVar5 | uVar3) ^ uVar4) + uVar7 + -0x14792c6f + local_60[9];
  *(uint *)(param_1 + 8) = *(int *)(param_1 + 8) + uVar5;
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + (uVar2 * 0x200000 | uVar2 >> 0xb) + uVar3;
  *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + uVar3;
  *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + uVar4;
  FUN_0083e885();
  return;
}

