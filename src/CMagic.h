#ifndef __CMAGIC_H__
#define __CMAGIC_H__

#include <string>

class CTexture;

class CMagic
{
  public:
    std::string name;
    std::string filename;
    CTexture *texture;
};

#endif
