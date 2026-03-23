
void FUN_00578760(void)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  undefined4 uVar6;
  code *pcVar7;
  
  if ((DAT_00917f48 != 0) &&
     (sVar1 = *(short *)(DAT_00917f48 + 4), sVar2 = FUN_00574b90(), sVar1 != sVar2)) {
    iVar4 = FUN_005771b0(DAT_009180d4);
    if (iVar4 == 0) {
      uVar6 = 0;
      FUN_00764760(0);
      FUN_00740a90(uVar6);
      pcVar7 = FUN_004bc8c0;
      FUN_0081e820(
                  "NotifyNowHost called.  (HOST CHANGED).  Exiting lobby since now host and previously kicked from game."
                  );
      uVar6 = FUN_0081e660();
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar6);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pcVar7);
      DAT_00917f78 = 1;
      uVar3 = FUN_00574b90();
      *(undefined2 *)(DAT_00917f48 + 4) = uVar3;
    }
    else {
      FUN_005738a0();
      DAT_00917f78 = 1;
      *(undefined4 *)(DAT_00917f48 + 0x42c) = 0;
      *(undefined4 *)(DAT_00917f48 + 0x428) = 0;
      *(undefined4 *)(DAT_00917f48 + 0x430) = 300;
      uVar6 = FUN_0081cb40("multi_message",&DAT_00884a48);
      FUN_0056fcb0(&DAT_00879854,uVar6);
      if (*(short *)(DAT_00917f48 + 4) != 0) {
        FUN_004baad0(0);
        FUN_004baad0(*(undefined2 *)(DAT_00917f48 + 4));
      }
      pcVar7 = FUN_004bc8c0;
      FUN_0081e820("NotifyNowHost called.  (HOST CHANGED)");
      uVar6 = FUN_0081e660();
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar6);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pcVar7);
      uVar3 = FUN_00574b90();
      *(undefined2 *)(DAT_00917f48 + 4) = uVar3;
      if (*(int *)(DAT_00917f48 + 8) == 3) {
        *(undefined4 *)(DAT_00917f48 + 8) = 2;
      }
    }
  }
  return;
}

