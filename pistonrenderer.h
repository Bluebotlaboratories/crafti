#ifndef PISTONRENDERER_H
#define PISTONRENDERER_H

#include "blockrenderer.h"

class PistonRenderer : public DumbBlockRenderer
{
public:
    virtual void renderSpecialBlock(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z, Chunk &c) override;
    virtual void geometryNormalBlock(const BLOCK_WDATA, const int /*local_x*/, const int /*local_y*/, const int /*local_z*/, const BLOCK_SIDE /*side*/, Chunk &/*c*/) override {};
    virtual bool isOpaque(const BLOCK_WDATA /*block*/) override { return false; }
    virtual bool isObstacle(const BLOCK_WDATA /*block*/) override { return true; }
    virtual bool isOriented(const BLOCK_WDATA /*block*/) override { return true; } // Oriented
    virtual bool isFullyOriented(const BLOCK_WDATA /*block*/) override { return false; } // Torch-like orientation

    virtual void tick(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) override;
    virtual bool isBlockShaped(const BLOCK_WDATA /*block*/) override { return true; }

    // Used for particles spawned on destruction
    virtual const TerrainAtlasEntry &destructionTexture(const BLOCK_WDATA block) override;

    virtual void removedBlock(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) override;

    virtual void drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y) override;

    virtual const char* getName(const BLOCK_WDATA block) override;

protected:
    enum PISTON_TYPE {
        PISTON_NORMAL = 0,
        PISTON_BODY,
        PISTON_HEAD
    };

    enum REDSTONE_STATE {
        OFF=0,
        ON
    };

    /// Bitmap stuff
    static const uint8_t piston_bit_shift = 3; // The amount to shift piston data by to give it room for the orientation or other additional data
    static const uint8_t piston_data_bits = 0b11 << piston_bit_shift; // Piston uses 2 bits of data, however, orientation data is stored in the first three bits, so the piston data has to be shifted by 3 (or more)
    static const uint8_t piston_power_bit_shift = 5;
    static const uint8_t piston_powered_bits = 0b1 << piston_power_bit_shift;
    static const std::vector<BLOCK_WDATA> unmovableBlocks;
};

#endif // PISTONRENDERER_H
