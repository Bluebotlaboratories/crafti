#include "stairrenderer.h"

constexpr GLFix StairRenderer::stair_height, StairRenderer::stair_width;

// Get stair texture
const TerrainAtlasEntry &StairRenderer::getStairTexture(const BLOCK_WDATA block) {
    switch (static_cast<STAIR_TYPE>((getBLOCKDATA(block) & stair_data_bits) >> stair_bit_shift)) {
        default:
            return terrain_atlas[6][12];
            break;
        case STAIR_STONE:
            return terrain_atlas[1][0];
            break;
        case STAIR_PLANKS_NORMAL:
            return terrain_atlas[4][0];
            break;
        case STAIR_WALL:
            return terrain_atlas[7][0];
            break;
        case STAIR_PLANKS_DARK:
            return terrain_atlas[6][12];
            break;
        case STAIR_PLANKS_BRIGHT:
            return terrain_atlas[6][13];
            break;
        case STAIR_COBBLESTONE:
            return terrain_atlas[0][1];
            break;
        case STAIR_NETHERRACK:
            return terrain_atlas[7][6];
            break;
    }
}

const TerrainAtlasEntry &StairRenderer::destructionTexture(const BLOCK_WDATA block) {
    return getStairTexture(block);
}

void StairRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    const TextureAtlasEntry &stair_top = getStairTexture(block).current;
    TextureAtlasEntry stair_sid = getStairTexture(block).current;

    stair_sid.top = stair_sid.top + (stair_sid.bottom - stair_sid.top) * 8 / 16;


    //////
    // GL CODE
    //////

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> stair_vertices;
    stair_vertices.reserve(40);


    // Stair Side
    stair_vertices.push_back({0, 0, 0, stair_sid.left, stair_sid.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_height, 0, stair_sid.left, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_width, stair_height, 0, stair_sid.right, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_width, 0, 0, stair_sid.right, stair_sid.bottom, TEXTURE_TRANSPARENT});

    // Stair Side
    stair_vertices.push_back({stair_width, 0, GLFix(0) + BLOCK_SIZE, stair_sid.left, stair_sid.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_width, stair_height, GLFix(0) + BLOCK_SIZE, stair_sid.left, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_height, GLFix(0) + BLOCK_SIZE, stair_sid.right, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, 0, GLFix(0) + BLOCK_SIZE, stair_sid.right, stair_sid.bottom, TEXTURE_TRANSPARENT});

    // Stair Back Side
    stair_vertices.push_back({0, 0, GLFix(0) + BLOCK_SIZE, stair_sid.left, stair_sid.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_height, 0 + BLOCK_SIZE, stair_sid.left, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_height, 0, stair_sid.right, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, 0, 0, stair_sid.right, stair_sid.bottom, TEXTURE_TRANSPARENT});

    // Stair (Front) Inside
    stair_vertices.push_back({(GLFix(0)) + stair_width, 0, 0, stair_sid.left, stair_sid.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({(GLFix(0)) + stair_width, stair_height, 0, stair_sid.left, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({(GLFix(0)) + stair_width, stair_height, 0 + BLOCK_SIZE, stair_sid.right, stair_sid.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({(GLFix(0)) + stair_width, 0, 0 + BLOCK_SIZE, stair_sid.right, stair_sid.bottom, TEXTURE_TRANSPARENT});

    // Stair Top
    stair_vertices.push_back({0, stair_height, 0, stair_top.left, stair_top.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_height, GLFix(0) + BLOCK_SIZE, stair_top.left, stair_top.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_width, stair_height, GLFix(0) + BLOCK_SIZE, stair_top.right, stair_top.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_width, stair_height, 0, stair_top.right, stair_top.bottom, TEXTURE_TRANSPARENT});

    
    ////////
    // STAIR TOP PART
    ////////
    // Get "texturemap" thingies for cake
    TextureAtlasEntry stair_top_top = getStairTexture(block).current;
    TextureAtlasEntry stair_top_side = getStairTexture(block).current;

    GLFix stair_top_left_texturemap = stair_top_side.right - (stair_top_side.right - stair_top_side.left) * 8 / 16;
    GLFix stair_top_right_texturemap = stair_top_side.left + (stair_top_side.right - stair_top_side.left) * 8 / 16;
    stair_top_top.right = stair_top_top.left + (stair_top_top.right - stair_top_top.left) * 8 / 16;

    GLFix stair_top_offset = BLOCK_SIZE / 2;
    GLFix stair_top_y_offset = BLOCK_SIZE / 2;
    GLFix stair_top_height = BLOCK_SIZE / 2;


    // Cake Side
    stair_vertices.push_back({0, stair_top_y_offset, 0, stair_top_side.left, stair_top_side.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, 0, stair_top_side.left, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset + stair_top_height, 0, stair_top_right_texturemap, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset, 0, stair_top_right_texturemap, stair_top_side.bottom, TEXTURE_TRANSPARENT});

    // Cake Side
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset, 0 + BLOCK_SIZE, stair_top_left_texturemap, stair_top_side.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset + stair_top_height, 0 + BLOCK_SIZE, stair_top_left_texturemap, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, 0 + BLOCK_SIZE, stair_top_side.right, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset, 0 + BLOCK_SIZE, stair_top_side.right, stair_top_side.bottom, TEXTURE_TRANSPARENT});

    // Cake Back Side
    stair_vertices.push_back({0, stair_top_y_offset, GLFix(0) + BLOCK_SIZE, stair_top_side.left, stair_top_side.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, 0 + BLOCK_SIZE, stair_top_side.left, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, 0, stair_top_side.right, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset, 0, stair_top_side.right, stair_top_side.bottom, TEXTURE_TRANSPARENT});

    // Cake (Front) Inside
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset, 0, stair_top_side.left, stair_top_side.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset + stair_top_height, 0, stair_top_side.left, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset + stair_top_height, 0 + BLOCK_SIZE, stair_top_side.right, stair_top_side.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset, stair_top_y_offset, 0 + BLOCK_SIZE, stair_top_side.right, stair_top_side.bottom, TEXTURE_TRANSPARENT});

    // Cake Top
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, 0, stair_top_top.left, stair_top_top.bottom, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({0, stair_top_y_offset + stair_top_height, GLFix(0) + BLOCK_SIZE - 0, stair_top_top.left, stair_top_top.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset - 0, stair_top_y_offset + stair_top_height, GLFix(0) + BLOCK_SIZE - 0, stair_top_top.right, stair_top_top.top, TEXTURE_TRANSPARENT});
    stair_vertices.push_back({stair_top_offset - 0, stair_top_y_offset + stair_top_height, 0, stair_top_top.right, stair_top_top.bottom, TEXTURE_TRANSPARENT});


    // Rotate stairs According To Face
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);

    // Rotate GL stuff
    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            nglRotateY(270);
            break;
        case BLOCK_FRONT:
            nglRotateY(90);
            break;
        case BLOCK_LEFT:
            nglRotateY(180);
            break;
        case BLOCK_RIGHT:
            nglRotateY(0);
            break;
    }

    glTranslatef(-BLOCK_SIZE / 2, -BLOCK_SIZE / 2, -BLOCK_SIZE / 2);

    for(auto&& v : stair_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void StairRenderer::geometryNormalBlock(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, getStairTexture(block).current, c);
}

AABB StairRenderer::getAABB(const BLOCK_WDATA /*block*/, GLFix x, GLFix y, GLFix z)
{
    return {x + 0, y, z + 0, x + 0 + stair_width, y + stair_height, z + 0 + stair_width};
}

void StairRenderer::drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry tex = getStairTexture(block).resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *StairRenderer::getName(const BLOCK_WDATA block)
{
    switch (static_cast<STAIR_TYPE>((getBLOCKDATA(block) & stair_data_bits) >> stair_bit_shift)) {
        default:
            return "Stairs";
            break;
        case STAIR_STONE:
            return "Stone Stairs";
            break;
        case STAIR_PLANKS_NORMAL:
            return "Oak Stairs";
            break;
        case STAIR_WALL:
            return "Brick Stairs";
            break;
        case STAIR_PLANKS_DARK:
            return "Dark Oak Stairs";
            break;
        case STAIR_PLANKS_BRIGHT:
            return "Bright Oak Stairs";
            break;
        case STAIR_COBBLESTONE:
            return "Cobblestone Stairs";
            break;
        case STAIR_NETHERRACK:
            return "Netherack Stairs";
            break;
    }
}