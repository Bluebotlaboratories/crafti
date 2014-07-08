#include "pressurerenderer.h"

#include "worldtask.h"

void PressurePlateRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    const TextureAtlasEntry &tex = terrain_atlas[3][getPOWERSTATE(block) ? 9 : 8].current;

    c.addUnalignedVertex(x, y + height, z, tex.left, tex.bottom, TEXTURE_DRAW_BACKFACE);
    c.addUnalignedVertex(x, y + height, z + BLOCK_SIZE, tex.left, tex.top, TEXTURE_DRAW_BACKFACE);
    c.addUnalignedVertex(x + BLOCK_SIZE, y + height, z + BLOCK_SIZE, tex.right, tex.top, TEXTURE_DRAW_BACKFACE);
    c.addUnalignedVertex(x + BLOCK_SIZE, y + height, z, tex.right, tex.bottom, TEXTURE_DRAW_BACKFACE);
}

AABB PressurePlateRenderer::getAABB(const BLOCK_WDATA /*block*/, GLFix x, GLFix y, GLFix z)
{
    return {x, y, z, x + BLOCK_SIZE, y + height, z + BLOCK_SIZE};
}

void PressurePlateRenderer::tick(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c)
{
    bool triggered = local_x + c.x * Chunk::SIZE == (world_task.x / BLOCK_SIZE).toInteger<int>()
            && local_y + c.y * Chunk::SIZE == (world_task.y / BLOCK_SIZE).toInteger<int>()
            && local_z + c.z * Chunk::SIZE == (world_task.z / BLOCK_SIZE).toInteger<int>();

    if(getPOWERSTATE(block) == triggered)
        return;

    c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATAPower(block, 0, triggered));
}

void PressurePlateRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, terrain_atlas[3][9].resized, false, dest, x, y);
}

const char *PressurePlateRenderer::getName(const BLOCK_WDATA)
{
    return "Pressure Plate";
}
