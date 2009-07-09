#include "CNPC.h"

class CZone;

namespace DawnInterface
{
    CNPC* createNewMobType( std::string typeID );
    CZone* getCurrentZone();
    void addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn, CZone *zone );
}

