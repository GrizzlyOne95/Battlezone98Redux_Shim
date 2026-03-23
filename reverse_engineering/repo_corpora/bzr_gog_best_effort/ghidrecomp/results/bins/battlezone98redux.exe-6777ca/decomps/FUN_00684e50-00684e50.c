
ColourValue * FUN_00684e50(ColourValue *param_1,uint param_2)

{
  Ogre::ColourValue::ColourValue
            (param_1,(float)((int)param_2 >> 0x10 & 0xff) / 255.0,
             (float)((int)param_2 >> 8 & 0xff) / 255.0,(float)(param_2 & 0xff) / 255.0,
             (float)((int)param_2 >> 0x18 & 0xff) / 255.0);
  return param_1;
}

