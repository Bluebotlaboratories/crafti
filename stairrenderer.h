#ifndef STAIRRENDERER_H
#define STAIRRENDERER_H

#include "blockrenderer.h"

class StairRenderer : public DumbBlockRenderer
{
public:
    virtual void renderSpecialBlock(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z, Chunk &c) override;
    virtual void geometryNormalBlock(const BLOCK_WDATA, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c) override;
    virtual bool isOpaque(const BLOCK_WDATA /*block*/) override { return false; }
    virtual bool isObstacle(const BLOCK_WDATA /*block*/) override { return true; }
    virtual bool isOriented(const BLOCK_WDATA /*block*/) override { return true; } // Not oriented (for extra data)
    virtual bool isFullyOriented(const BLOCK_WDATA /*block*/) override { return false; } // Torch-like orientation

    virtual bool isBlockShaped(const BLOCK_WDATA /*block*/) override { return false; }
    virtual AABB getAABB(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z) override;

    virtual void drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y) override;

    // Used for particles spawned on destruction
    virtual const TerrainAtlasEntry &destructionTexture(const BLOCK_WDATA block) override;

    virtual const char* getName(const BLOCK_WDATA) override;

protected:
    const TerrainAtlasEntry getStairTexture(const BLOCK_WDATA block);

    static constexpr GLFix stair_height = BLOCK_SIZE / 16 * 8;
    static constexpr GLFix stair_width = BLOCK_SIZE;

    /// Bitmap stuff
    static constexpr uint8_t stair_bit_shift = 3; // The amount to shift cake data by to give it room for the orientation or other additional data
    static constexpr uint8_t stair_data_bits = 0b111 << stair_bit_shift; // Stairs use 3 bits of data, however, orientation data is stored in the first three bits, so the cake data has to be shifted by 3 (or more)

    enum STAIR_TYPE {
        STAIR_STONE=0,
        STAIR_PLANKS_NORMAL,
        STAIR_WALL,
        STAIR_PLANKS_DARK,
        STAIR_PLANKS_BRIGHT,
        STAIR_COBBLESTONE,
        STAIR_NETHERRACK,
    };
};

#endif // STAIRRENDERER_H
