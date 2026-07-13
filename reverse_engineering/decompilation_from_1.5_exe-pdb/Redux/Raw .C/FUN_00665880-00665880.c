
OgreTheoraVideoManager * __thiscall FUN_00665880(OgreTheoraVideoManager *param_1,uint param_2)

{
  Ogre::OgreTheoraVideoManager::~OgreTheoraVideoManager(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

