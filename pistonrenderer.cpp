#include <algorithm>
#include "pistonrenderer.h"

// Define blocks which the piston cannot move
const std::vector<BLOCK_WDATA> PistonRenderer::unmovableBlocks = {
    BLOCK_BEDROCK,
    BLOCK_FLOWER,
    BLOCK_WHEAT,
    BLOCK_MUSHROOM,
    BLOCK_REDSTONE_SWITCH,
    BLOCK_REDSTONE_TORCH,
    BLOCK_BEDROCK,
    BLOCK_DOOR,
    getBLOCKWDATA(BLOCK_PISTON, PISTON_HEAD << piston_state_bit_shift)
};



bool PistonRenderer::isBlockMovable(BLOCK_WDATA block) {
    if (std::find(unmovableBlocks.begin(), unmovableBlocks.end(), getBLOCK(block)) == unmovableBlocks.end() && std::find(unmovableBlocks.begin(), unmovableBlocks.end(), block) == unmovableBlocks.end()) {
        if (getBLOCK(block) == BLOCK_PISTON) {
            const PISTON_STATE piston_state = static_cast<PISTON_STATE>((getBLOCKDATA(block) & piston_state_bits) >> piston_state_bit_shift);
            if (piston_state != PISTON_NORMAL) {
                return true;
            }
        }

        return true;
    }

    return false;
}

VECTOR3 PistonRenderer::get_piston_block_relative(int local_x, int local_y, int local_z, const BLOCK_SIDE side, const int8_t offset) {
    VECTOR3 piston_block_relative;

    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            piston_block_relative.x = local_x;
            piston_block_relative.y = local_y;
            piston_block_relative.z = local_z+offset;
            break;
        case BLOCK_FRONT:
            piston_block_relative.x = local_x;
            piston_block_relative.y = local_y;
            piston_block_relative.z = local_z-offset;
            break;
        case BLOCK_LEFT:
            piston_block_relative.x = local_x-offset;
            piston_block_relative.y = local_y;
            piston_block_relative.z = local_z;
            break;
        case BLOCK_RIGHT:
            piston_block_relative.x = local_x+offset;
            piston_block_relative.y = local_y;
            piston_block_relative.z = local_z;
            break;
        case BLOCK_TOP:
            piston_block_relative.x = local_x;
            piston_block_relative.y = local_y+offset;
            piston_block_relative.z = local_z;
            break;
        case BLOCK_BOTTOM:
            piston_block_relative.x = local_x;
            piston_block_relative.y = local_y-offset;
            piston_block_relative.z = local_z;
            break;
    }

    return piston_block_relative;
}

std::vector<VERTEX> PistonRenderer::get_piston_normal_vertices(const PISTON_TYPE piston_type) {
    const TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    const TextureAtlasEntry piston_back = terrain_atlas[13][6].current;
    
    TextureAtlasEntry piston_front = terrain_atlas[11][6].current;
    if (piston_type == STICKY_PISTON) {
        piston_front = terrain_atlas[10][6].current;
    }

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(24);

    // Piston Front
    piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    return piston_vertices;
}

std::vector<VERTEX> PistonRenderer::get_piston_body_vertices() {
    const TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    const TextureAtlasEntry piston_back = terrain_atlas[13][6].current;
    const TextureAtlasEntry piston_front = terrain_atlas[14][6].current;

    const GLFix piston_head_size = BLOCK_SIZE / 4;

    const GLFix piston_body_texturemap_top = piston_side.bottom - ((piston_side.bottom - piston_side.top) * 12 / 16);

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(24);

    // Piston Front
    piston_vertices.push_back({0, 0, piston_head_size, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    return piston_vertices;
}

std::vector<VERTEX> PistonRenderer::get_piston_head_vertices(const PISTON_TYPE piston_type) {
    const TextureAtlasEntry piston_side = terrain_atlas[12][6].current;

    TextureAtlasEntry piston_front = terrain_atlas[11][6].current;
    TextureAtlasEntry piston_back = terrain_atlas[11][6].current;
    if (piston_type == STICKY_PISTON) {
        piston_front = terrain_atlas[10][6].current;
    }

    const GLFix piston_head_size = BLOCK_SIZE / 4;

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(40);

    const GLFix piston_head_bottom_texturemap = piston_side.top + ((piston_side.bottom - piston_side.top) * 4 / 16);

    // Piston Front
    piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, piston_head_size, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});


    // Piston Neck
    const GLFix piston_neck_size = BLOCK_SIZE * 4 / 16;
    const GLFix piston_neck_length = GLFix(BLOCK_SIZE) - piston_head_size;
    const GLFix piston_neck_offset = (GLFix(BLOCK_SIZE) - piston_neck_size) * GLFix(0.5f);

    // Piston "Neck" Top
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston "Neck" Bottom
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston "Neck" Left
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston "Neck" Right
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    return piston_vertices;
}



const TerrainAtlasEntry &PistonRenderer::destructionTexture(const BLOCK_WDATA /*block*/) {
    return terrain_atlas[4][0];
}

void PistonRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> piston_vertices;

    const PISTON_STATE piston_state = static_cast<PISTON_STATE>((getBLOCKDATA(block) & piston_state_bits) >> piston_state_bit_shift);
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_type_bits) >> piston_type_bit_shift);
    switch (piston_state) {
        case PISTON_NORMAL:
            piston_vertices = get_piston_normal_vertices(piston_type);
            break;
        case PISTON_BODY:
            piston_vertices = get_piston_body_vertices();
            break;
        case PISTON_HEAD:
            piston_vertices = get_piston_head_vertices(piston_type);
            break;
    }


    // Rotate Piston According To Face
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);

    // Rotate GL stuff
    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            nglRotateY(180);
            break;
        case BLOCK_FRONT:
            nglRotateY(0);
            break;
        case BLOCK_LEFT:
            nglRotateY(90);
            break;
        case BLOCK_RIGHT:
            nglRotateY(270);
            break;
        case BLOCK_BOTTOM:
            nglRotateX(270);
            break;
        case BLOCK_TOP:
            nglRotateX(90);
            break;
    }

    glTranslatef(-BLOCK_SIZE / 2, -BLOCK_SIZE / 2, -BLOCK_SIZE / 2);

    for(auto&& v : piston_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void PistonRenderer::tick(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) {
    // Get proper piston head coordinates
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    bool poweredProperly = false;

    // Piston coordinate stuff
    VECTOR3 pistonHeadCoordinates = get_piston_block_relative(local_x, local_y, local_z, side, 1);
    VECTOR3 blockToPushCoordinates = get_piston_block_relative(local_x, local_y, local_z, side, 2);

    // Calculate piston-side-dependent variables
    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
            );
            break;
        case BLOCK_FRONT:
            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_LEFT:
            poweredProperly = (
                c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_RIGHT:
            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_TOP:
            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_BOTTOM:
            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
    }

    // Get the piston's powered-state and its type
    const uint8_t piston_powered = static_cast<uint8_t>((getBLOCKDATA(block) & piston_power_state_bits) >> piston_power_state_bit_shift);
    const PISTON_STATE piston_state = static_cast<PISTON_STATE>((getBLOCKDATA(block) & piston_state_bits) >> piston_state_bit_shift);
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_type_bits) >> piston_type_bit_shift);

    // If the piston's power state has changed and it isn't a piston_head
    if(piston_powered != poweredProperly && piston_state != PISTON_HEAD) {

        // Get the piston's data and prepare it by resetting its powered state
        uint8_t piston_data = getBLOCKDATA(block) ^ (piston_powered << piston_power_state_bit_shift); // Set pre-existing power bit to zero

        // If it is powered "properly" (not by the face)
        if (poweredProperly) {
            // Get the block to push
            BLOCK_WDATA blockToPush = c.getGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z);

            bool piston_pushable = false;
            bool piston_movable = true;

            // If the block to push isn't an unmovable block
            for (int i = 1; i <= push_limit+1; i++) {
                VECTOR3 block_to_check = get_piston_block_relative(local_x, local_y, local_z, side, i);

                // Test that blocks are movable
                if (!isBlockMovable(blockToPush)) {
                    piston_movable = false;
                }

                if (c.getGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z) == BLOCK_AIR) {
                    piston_pushable = true;
                    break;
                }
            }

            if (piston_pushable && piston_movable) {
                piston_data = piston_data ^ (piston_state << piston_state_bit_shift); // Set pre-existing piston type bits to zero

                // Set the block to the piston body
                c.changeLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data | poweredProperly << piston_power_state_bit_shift | PISTON_BODY << piston_state_bit_shift));
                
                BLOCK_WDATA block_to_move;
                VECTOR3 block_to_check;
                BLOCK_WDATA new_block_to_move;

                for (int i = 1; i <= push_limit+1; i++) {
                    block_to_check = get_piston_block_relative(local_x, local_y, local_z, side, i);

                    if (i == 1) {
                        block_to_move = c.getGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z);
                        if (block_to_move == BLOCK_AIR) {
                            break;
                        }
                        continue;
                    }

                    if (c.getGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z) == BLOCK_AIR) {
                        c.changeGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z, block_to_move);
                        break;
                    }
                    
                    new_block_to_move = c.getGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z);
                    c.changeGlobalBlockRelative(block_to_check.x, block_to_check.y, block_to_check.z, block_to_move);
                    block_to_move = new_block_to_move;
                }

                // Set the corresponding block to the piston head
                c.changeGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, getBLOCKWDATA(BLOCK_PISTON, side | PISTON_HEAD << piston_state_bit_shift | piston_type << piston_type_bit_shift));
            }
        } else {
            // Reset the piston data's piston type
            piston_data = piston_data ^ (piston_state << piston_state_bit_shift); // Set pre-existing piston data bits to zero

            // Update the piston type
            c.changeLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data));

            // Remove the piston head only if it is actually extended
            if (piston_state == PISTON_BODY) {
                if (piston_type == STICKY_PISTON) {
                    BLOCK_WDATA blockToPull = c.getGlobalBlockRelative(blockToPushCoordinates.x, blockToPushCoordinates.y, blockToPushCoordinates.z);

                    if (isBlockMovable(blockToPull)) {
                        c.changeGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, blockToPull);
                        c.changeGlobalBlockRelative(blockToPushCoordinates.x, blockToPushCoordinates.y, blockToPushCoordinates.z, BLOCK_AIR);
                    } else {
                        c.changeGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, BLOCK_AIR);
                    }
                } else {
                    c.changeGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, BLOCK_AIR);
                }
            }
        }
    }
}

void PistonRenderer::removedBlock(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) {
    // Check the piston type
    const PISTON_STATE piston_state = static_cast<PISTON_STATE>((getBLOCKDATA(block) & piston_state_bits) >> piston_state_bit_shift);

    // If the piston isn't a "normal" piston
    if (piston_state != PISTON_NORMAL) {
        // Get side-dependant variable thingies
        BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
        VECTOR3 pistonBodyCoordinates;
        VECTOR3 pistonHeadCoordinates;

        // Set the piston's head/body to air, thereby removing it depending on which type the destroyed one is
        switch (piston_state) {
            case PISTON_NORMAL:
                break; // Stop compiler warnings
            case PISTON_BODY:
                pistonHeadCoordinates = get_piston_block_relative(local_x, local_y, local_z, side, 1);
                c.changeGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, getBLOCK(BLOCK_AIR));
                break;
            case PISTON_HEAD:
                pistonBodyCoordinates = get_piston_block_relative(local_x, local_y, local_z, side, -1);
                c.changeGlobalBlockRelative(pistonBodyCoordinates.x, pistonBodyCoordinates.y, pistonBodyCoordinates.z, getBLOCK(BLOCK_AIR));
                break;
        }
    }
}

void PistonRenderer::drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y)
{
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_type_bits) >> piston_type_bit_shift);

    if (piston_type == STICKY_PISTON) {
        BlockRenderer::drawTextureAtlasEntry(*terrain_resized, terrain_atlas[10][6].resized, dest, x, y);
    } else {
        BlockRenderer::drawTextureAtlasEntry(*terrain_resized, terrain_atlas[11][6].resized, dest, x, y);
    }
}

const char *PistonRenderer::getName(const BLOCK_WDATA block)
{
    // Mainly just for debug as PISTON_BODY and PISTON_HEAD should never end up in the inventory
    const PISTON_STATE piston_state = static_cast<PISTON_STATE>((getBLOCKDATA(block) & piston_state_bits) >> piston_state_bit_shift);
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_type_bits) >> piston_type_bit_shift);

    if (piston_type == STICKY_PISTON) {
        switch (piston_state) {
            case PISTON_NORMAL:
                return "Sticky Piston";
                break;
            case PISTON_BODY:
                return "Sticky Piston Body";
                break;
            case PISTON_HEAD:
                return "Sticky Piston Head";
                break;
        }
    } else {
        switch (piston_state) {
            case PISTON_NORMAL:
                return "Piston";
                break;
            case PISTON_BODY:
                return "Piston Body";
                break;
            case PISTON_HEAD:
                return "Piston Head";
                break;
        }
    }
    
    return "Piston";
}