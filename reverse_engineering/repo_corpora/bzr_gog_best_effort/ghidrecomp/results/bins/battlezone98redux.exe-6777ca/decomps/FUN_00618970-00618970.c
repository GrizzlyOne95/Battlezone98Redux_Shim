
void FUN_00618970(void)

{
  DAT_00920ecc = 0;
  if (DAT_02a13e28 == 0.0) {
    FUN_0081e0c0();
  }
  else {
    if (DAT_02a13e7c != 0.0) {
      FUN_0081e0c0("Frame rates over last period: Max FPS %f, Min FPS %f\n",(double)DAT_02a13e7c,
                   (double)DAT_02a13df4);
    }
    FUN_0081e0c0("Game Simulation Finished: Max FPS %f, Min FPS %f\n",(double)DAT_02a13e28,
                 (double)DAT_02a13e2c);
  }
  FUN_00681e70();
  DAT_009183dc = 0;
  FUN_00618370();
  _chdir(&DAT_02cf0000);
  return;
}

