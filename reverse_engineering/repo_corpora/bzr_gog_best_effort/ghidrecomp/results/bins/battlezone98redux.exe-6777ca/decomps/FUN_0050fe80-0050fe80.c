
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_0050fe80(char *param_1,int param_2)

{
  uchar uVar1;
  char *pcVar2;
  ColourValue *pCVar3;
  byte *pbVar4;
  int iVar5;
  ushort in_FPUControlWord;
  float10 fVar6;
  undefined1 auStack_102dc [16];
  Image aIStack_102cc [44];
  undefined4 uStack_102a0;
  float fStack_1029c;
  float fStack_10298;
  float fStack_10294;
  uint uStack_1028c;
  int iStack_10288;
  uint uStack_10284;
  uint uStack_10280;
  int iStack_1027c;
  int iStack_10278;
  int iStack_10274;
  int iStack_10270;
  int iStack_1026c;
  int iStack_10268;
  uint uStack_10264;
  int iStack_10260;
  uint uStack_1025c;
  uint uStack_10258;
  uint uStack_10254;
  int iStack_10250;
  int iStack_1024c;
  int iStack_10248;
  int iStack_10244;
  uint uStack_10240;
  float fStack_1023c;
  int iStack_10238;
  int iStack_10234;
  int iStack_10230;
  int iStack_1022c;
  int iStack_10228;
  int iStack_10224;
  undefined4 uStack_10220;
  undefined4 uStack_1021c;
  int iStack_10218;
  int iStack_10214;
  int iStack_10210;
  int iStack_1020c;
  char *pcStack_10208;
  int iStack_10204;
  uchar *puStack_10200;
  int iStack_101fc;
  undefined1 *puStack_101f8;
  int iStack_101f4;
  int iStack_101f0;
  int iStack_101ec;
  int iStack_101e8;
  int iStack_101e4;
  byte *pbStack_101e0;
  int iStack_101dc;
  int iStack_101d8;
  int iStack_101d4;
  int iStack_101d0;
  int iStack_101cc;
  uint uStack_101c8;
  int iStack_101c4;
  undefined4 uStack_101c0;
  int iStack_101bc;
  int iStack_101b8;
  int iStack_101b4;
  int iStack_101b0;
  byte *pbStack_101a8;
  int iStack_101a0;
  int iStack_10198;
  uint uStack_10194;
  PixelBox *pPStack_10190;
  uint uStack_1018c;
  float *pfStack_10188;
  int iStack_10184;
  int iStack_10180;
  ushort *puStack_1017c;
  ushort *puStack_10178;
  int iStack_10174;
  int iStack_10170;
  int iStack_1016c;
  int iStack_10168;
  byte bStack_10163;
  byte bStack_10162;
  byte bStack_10161;
  uchar *puStack_10160;
  int iStack_1015c;
  undefined1 *puStack_10158;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_10154 [24];
  float fStack_1013c;
  float fStack_10138;
  float fStack_10130;
  float fStack_1012c;
  float fStack_10128;
  float fStack_10120;
  float fStack_1011c;
  float fStack_10118;
  float fStack_10114;
  float fStack_10110;
  uchar auStack_1010c [65536];
  char local_10c [256];
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  strncpy(local_10c,param_1,0x100);
  pcStack_10208 = (char *)FUN_004fbaf0(local_10c,0x2e);
  if (pcStack_10208 != (char *)0x0) {
    strncpy(pcStack_10208,".BMP",(size_t)(local_c + -(int)pcStack_10208));
  }
  iStack_1015c = param_2 * 4;
  iStack_1022c = iStack_1015c * iStack_1015c;
  puStack_101f8 = malloc(iStack_1022c * 0x300);
  uStack_101c0 = FUN_0077c670();
  puStack_10158 = puStack_101f8;
  pPStack_10190 = (PixelBox *)FUN_0077b370();
  if (pPStack_10190 == (PixelBox *)0x0) {
    for (iStack_1020c = 0; iStack_1020c < 0x100; iStack_1020c = iStack_1020c + 1) {
      for (iStack_101e8 = 0; iStack_101e8 < iStack_1015c; iStack_101e8 = iStack_101e8 + 1) {
        for (iStack_101e4 = 0; iStack_101e4 < iStack_1015c; iStack_101e4 = iStack_101e4 + 1) {
          *puStack_10158 = 0xff;
          puStack_10158[1] = 0;
          puStack_10158[2] = 0xff;
          puStack_10158 = puStack_10158 + 3;
        }
      }
    }
  }
  else {
    iStack_10204 = FUN_0050cd60();
    iStack_10218 = FUN_0050cd80();
    uStack_10284 = FUN_0050cdf0();
    for (uStack_10194 = 0; uStack_10194 < uStack_10284; uStack_10194 = uStack_10194 + 1) {
      pcVar2 = (char *)FUN_00780db0(uStack_10194);
      if (*pcVar2 == '\0') {
        for (iStack_101f4 = 0; iStack_101f4 < iStack_1015c; iStack_101f4 = iStack_101f4 + 1) {
          for (iStack_101fc = 0; iStack_101fc < iStack_1015c; iStack_101fc = iStack_101fc + 1) {
            *puStack_10158 = 0xff;
            puStack_10158[1] = 0;
            puStack_10158[2] = 0xff;
            puStack_10158 = puStack_10158 + 3;
          }
        }
      }
      else {
        pfStack_10188 = (float *)FUN_0050ce10(uStack_10194);
        iStack_10228 = (int)((float)iStack_10204 * *pfStack_10188);
        iStack_10214 = (int)((float)iStack_10218 * pfStack_10188[1]);
        iStack_10260 = (int)((float)iStack_10204 * (*pfStack_10188 + pfStack_10188[2]));
        iStack_10268 = (int)((float)iStack_10218 * (pfStack_10188[1] + pfStack_10188[3]));
        iStack_1027c = iStack_10260 - iStack_10228;
        iStack_1024c = iStack_10268 - iStack_10214;
        iStack_10198 = FUN_0043d130(iStack_1027c / iStack_1015c,1);
        iStack_101bc = FUN_0043d130(iStack_1024c / iStack_1015c,1);
        iStack_10248 = iStack_10198 * iStack_101bc;
        iStack_101b4 = iStack_1015c;
        while (iStack_101b4 = iStack_101b4 + -1, -1 < iStack_101b4) {
          for (iStack_101b8 = 0; iStack_101b8 < iStack_1015c; iStack_101b8 = iStack_101b8 + 1) {
            if (*(int *)(pPStack_10190 + 0x1c) == 0x11) {
              iStack_10170 = 0;
              iStack_10168 = 0;
              iStack_1016c = 0;
              for (iStack_101cc = 0; iStack_101cc < iStack_101bc; iStack_101cc = iStack_101cc + 1) {
                iStack_10230 = iStack_101b4 * iStack_101bc + iStack_10214 + iStack_101cc;
                for (iStack_101d8 = 0; iStack_101d8 < iStack_10198; iStack_101d8 = iStack_101d8 + 1)
                {
                  iStack_10238 = iStack_101b8 * iStack_10198 + iStack_10228 + iStack_101d8;
                  iVar5 = ((int)(iStack_10230 + (iStack_10230 >> 0x1f & 3U)) >> 2) *
                          ((int)(iStack_10204 + (iStack_10204 >> 0x1f & 3U)) >> 2) +
                          ((int)(iStack_10238 + (iStack_10238 >> 0x1f & 3U)) >> 2);
                  uStack_10220 = *(undefined4 *)(*(int *)(pPStack_10190 + 0x18) + iVar5 * 8);
                  uStack_1021c = *(undefined4 *)(*(int *)(pPStack_10190 + 0x18) + 4 + iVar5 * 8);
                  puStack_10178 = (ushort *)&uStack_10220;
                  puStack_1017c = (ushort *)((int)&uStack_10220 + 2);
                  uStack_1028c = __aullshr();
                  uStack_1028c = uStack_1028c & 3;
                  switch(uStack_1028c) {
                  case 0:
                    iStack_10170 = (uint)(*puStack_10178 >> 0xb) * 3 + iStack_10170;
                    iStack_10168 = (uint)(*puStack_10178 >> 0xb) * 3 + iStack_10168;
                    iStack_1016c = (uint)(*puStack_10178 >> 0xb) * 3 + iStack_1016c;
                    break;
                  case 1:
                    iStack_10170 = (uint)(*puStack_1017c >> 0xb) + iStack_10170 +
                                   (uint)(*puStack_10178 >> 0xb) * 2;
                    iStack_10168 = (uint)(*puStack_1017c >> 5 & 0x3f) + iStack_10168 +
                                   (uint)(*puStack_10178 >> 5 & 0x3f) * 2;
                    iStack_1016c = (uint)(*puStack_1017c & 0x1f) + iStack_1016c +
                                   (uint)(*puStack_10178 & 0x1f) * 2;
                    break;
                  case 2:
                    iStack_10170 = (uint)(*puStack_10178 >> 0xb) + iStack_10170 +
                                   (uint)(*puStack_1017c >> 0xb) * 2;
                    iStack_10168 = (uint)(*puStack_10178 >> 5 & 0x3f) + iStack_10168 +
                                   (uint)(*puStack_1017c >> 5 & 0x3f) * 2;
                    iStack_1016c = (uint)(*puStack_10178 & 0x1f) + iStack_1016c +
                                   (uint)(*puStack_1017c & 0x1f) * 2;
                    break;
                  case 3:
                    iStack_10170 = (uint)(*puStack_1017c >> 0xb) * 3 + iStack_10170;
                    iStack_10168 = (uint)(*puStack_1017c >> 5 & 0x3f) * 3 + iStack_10168;
                    iStack_1016c = (uint)(*puStack_1017c & 0x1f) * 3 + iStack_1016c;
                  }
                  uStack_10240 = uStack_1028c;
                }
              }
              iStack_10174 = iStack_10248 * 3;
              iStack_10170 = ((iStack_10170 * 2 + iStack_10174) * 0xff) / (iStack_10248 * 0xba);
              iStack_10168 = ((iStack_10168 * 2 + iStack_10174) * 0xff) / (iStack_10248 * 0x17a);
              iStack_1016c = ((iStack_1016c * 2 + iStack_10174) * 0xff) / (iStack_10248 * 0xba);
              *puStack_10158 = (undefined1)iStack_1016c;
              puStack_10158[1] = (undefined1)iStack_10168;
              puStack_10158[2] = (undefined1)iStack_10170;
              puStack_10158 = puStack_10158 + 3;
            }
            else {
              Ogre::ColourValue::ColourValue((ColourValue *)&fStack_1029c,0.0,0.0,0.0,0.0);
              for (iStack_101d0 = 0; iStack_101d0 < iStack_101bc; iStack_101d0 = iStack_101d0 + 1) {
                uStack_10280 = iStack_101b4 * iStack_101bc + iStack_101d0;
                for (iStack_101c4 = 0; iStack_101c4 < iStack_10198; iStack_101c4 = iStack_101c4 + 1)
                {
                  uStack_10254 = iStack_101b8 * iStack_10198 + iStack_101c4;
                  pCVar3 = (ColourValue *)
                           Ogre::PixelBox::getColourAt
                                     (pPStack_10190,(uint)auStack_102dc,uStack_10254,uStack_10280);
                  Ogre::ColourValue::operator+=((ColourValue *)&fStack_1029c,pCVar3);
                }
              }
              Ogre::ColourValue::operator/=((ColourValue *)&fStack_1029c,(float)iStack_10248);
              fVar6 = (float10)FUN_00461fd0(fStack_10294 * 255.0 + 0.5);
              uStack_10258 = in_FPUControlWord | 0xc00;
              iStack_10274 = (int)ROUND(fVar6);
              *puStack_10158 = (undefined1)iStack_10274;
              puStack_10158 = puStack_10158 + 1;
              fVar6 = (float10)FUN_00461fd0(fStack_10298 * 255.0 + 0.5);
              uStack_1025c = in_FPUControlWord | 0xc00;
              iStack_10278 = (int)ROUND(fVar6);
              *puStack_10158 = (undefined1)iStack_10278;
              puStack_10158 = puStack_10158 + 1;
              fVar6 = (float10)FUN_00461fd0(fStack_1029c * 255.0 + 0.5);
              uStack_10264 = in_FPUControlWord | 0xc00;
              iStack_10288 = (int)ROUND(fVar6);
              *puStack_10158 = (undefined1)iStack_10288;
              puStack_10158 = puStack_10158 + 1;
            }
          }
        }
      }
    }
    FUN_0077b470();
  }
  iStack_10224 = (int)(DAT_0091738c * DAT_02cc50e4);
  iStack_10244 = (int)(DAT_00917394 * DAT_02cc50e4);
  iStack_10210 = (int)(DAT_00917390 * DAT_02cc50e4);
  iStack_10234 = (int)(DAT_00917388 * DAT_02cc50e4);
  uStack_1018c = ((iStack_10244 - iStack_10224) + 1) * param_2;
  uStack_101c8 = ((iStack_10234 - iStack_10210) + 1) * param_2;
  FUN_007d6a70("Writing %dx%d large map to %s\n",uStack_1018c,uStack_101c8,local_10c);
  for (iStack_101a0 = 0; iStack_101a0 < 0x100; iStack_101a0 = iStack_101a0 + 1) {
    for (iStack_101b0 = 0; iStack_101b0 < 0x100; iStack_101b0 = iStack_101b0 + 1) {
      uVar1 = FUN_0047fed0(0xff,((iStack_101b0 + 0x40) * iStack_101a0) / 0xff);
      auStack_1010c[iStack_101b0 + iStack_101a0 * 0x100] = uVar1;
    }
  }
  iStack_101f0 = uStack_1018c * -3;
  puStack_10200 = malloc(uStack_1018c * uStack_101c8 * 3);
  puStack_10160 = puStack_10200 + (uStack_101c8 - 1) * uStack_1018c * 3;
  fStack_1023c = 1.0 / (float)param_2;
  uStack_102a0 = 3;
  for (iStack_10180 = iStack_10210; iStack_10180 <= iStack_10234; iStack_10180 = iStack_10180 + 1) {
    for (iStack_10184 = iStack_10224; iStack_10184 <= iStack_10244; iStack_10184 = iStack_10184 + 1)
    {
      iStack_1026c = FUN_00780e80(iStack_10184,iStack_10180,&fStack_1012c,&fStack_1013c);
      pbVar4 = (byte *)FUN_0050ce30(iStack_10184,iStack_10180);
      fStack_1011c = (float)*pbVar4;
      pbVar4 = (byte *)FUN_0050ce30(iStack_10184 + 1,iStack_10180);
      fStack_10118 = (float)*pbVar4;
      pbVar4 = (byte *)FUN_0050ce30(iStack_10184 + 1,iStack_10180 + 1);
      fStack_10114 = (float)*pbVar4;
      pbVar4 = (byte *)FUN_0050ce30(iStack_10184,iStack_10180 + 1);
      fStack_10110 = (float)*pbVar4;
      pbStack_101e0 =
           puStack_101f8 +
           (iStack_1026c * iStack_1022c +
            (int)((float)(iStack_1015c + -1) * fStack_1013c) * iStack_1015c +
           (int)((float)(iStack_1015c + -1) * fStack_1012c)) * 3;
      iStack_10270 = ((int)(((fStack_10138 - fStack_1013c) * (float)iStack_1015c) / (float)param_2)
                      * iStack_1015c +
                     (int)(((fStack_10128 - fStack_1012c) * (float)iStack_1015c) / (float)param_2))
                     * 3;
      iStack_10250 = ((int)(((fStack_10130 - fStack_1013c) * (float)iStack_1015c) / (float)param_2)
                      * iStack_1015c +
                     (int)(((fStack_10120 - fStack_1012c) * (float)iStack_1015c) / (float)param_2))
                     * 3;
      for (iStack_101d4 = 0; iStack_101d4 < param_2; iStack_101d4 = iStack_101d4 + 1) {
        pbStack_101a8 = pbStack_101e0;
        for (iStack_101dc = 0; iStack_101dc < param_2; iStack_101dc = iStack_101dc + 1) {
          bStack_10162 = *pbStack_101a8;
          bStack_10161 = pbStack_101a8[1];
          bStack_10163 = pbStack_101a8[2];
          FUN_0050f6e0(((float)iStack_101dc + 0.5) * fStack_1023c,
                       ((float)iStack_101d4 + 0.5) * fStack_1023c,fStack_1011c,fStack_10118,
                       fStack_10114,fStack_10110);
          iStack_101ec = FUN_0083f040();
          bStack_10163 = auStack_1010c[iStack_101ec + (uint)bStack_10163 * 0x100];
          bStack_10161 = auStack_1010c[iStack_101ec + (uint)bStack_10161 * 0x100];
          bStack_10162 = auStack_1010c[iStack_101ec + (uint)bStack_10162 * 0x100];
          *puStack_10160 = bStack_10162;
          puStack_10160[1] = bStack_10161;
          puStack_10160[2] = bStack_10163;
          puStack_10160 = puStack_10160 + 3;
          pbStack_101a8 = pbStack_101a8 + iStack_10270;
        }
        puStack_10160 = puStack_10160 + iStack_101f0 + param_2 * -3;
        pbStack_101e0 = pbStack_101e0 + iStack_10250;
      }
      puStack_10160 = puStack_10160 + (param_2 * 3 - param_2 * iStack_101f0);
    }
    puStack_10160 = puStack_10160 + param_2 * iStack_101f0 + uStack_1018c * -3;
  }
  Ogre::Image::Image(aIStack_102cc);
  Ogre::Image::loadDynamicImage
            (aIStack_102cc,puStack_10200,uStack_1018c,uStack_101c8,1,10,false,1,'\0');
  basic_string<>(local_10c);
  Ogre::Image::save(aIStack_102cc,abStack_10154);
  ~basic_string<>();
  free(puStack_10200);
  free(puStack_101f8);
  Ogre::Image::~Image(aIStack_102cc);
  FUN_0083e885();
  return;
}

