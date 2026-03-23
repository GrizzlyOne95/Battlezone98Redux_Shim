
void FUN_006c85ef(void)

{
  char cVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  FUN_006d8cc0(5,0);
  cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -200);
  if (cVar1 == '\0') {
    FUN_006d8cc0(0x2728,0);
    cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0xb4);
    if (cVar1 == '\0') {
      FUN_006d8cc0(0x2726,0);
      cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0x94);
      if (cVar1 == '\0') {
        FUN_006d8cc0(0x2719,0);
        cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0xd0);
        if (cVar1 == '\0') {
          FUN_006d8cc0(0x271d,0);
          cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0xa4);
          if (cVar1 == '\0') {
            FUN_006d8cc0(0x271e,0);
            cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0xc0);
            if (cVar1 == '\0') {
              FUN_006d8cc0(0x14,0);
              cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0x84);
              if (cVar1 == '\0') {
                FUN_006d8cc0(0x2749,0);
                cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0x8c);
                if (cVar1 == '\0') {
                  FUN_006d8cc0(0x2736,0);
                  cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0x9c);
                  if (cVar1 == '\0') {
                    FUN_006d8cc0(0x274a,0);
                    cVar1 = FUN_006ab920(*(undefined4 *)(unaff_EBP + 8),unaff_EBP + -0xac);
                    if (cVar1 == '\0') goto LAB_006c87db;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_006cb2b0();
LAB_006c87db:
  cVar1 = FUN_006cb280();
  if (cVar1 == '\0') {
    FUN_006be750();
  }
  FUN_006c6df0();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

