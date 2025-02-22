#include "woolrenderer.h"


// Get wool texture
TerrainAtlasEntry WoolRenderer::getWoolTexture(const BLOCK_WDATA block) {
    TerrainAtlasEntry tae = terrain_atlas[0][4];

    switch (static_cast<COLOUR>(getBLOCKDATA(block))) {
        case WHITE_WOOL:
            tae = terrain_atlas[0][4];
            break;
        case ORANGE_WOOL:
            tae = terrain_atlas[2][13];
            break;
        case MAGENTA_WOOL:
            tae = terrain_atlas[2][12];
            break;
        case LIGHT_BLUE_WOOL:
            tae = terrain_atlas[2][11];
            break;
        case YELLOW_WOOL:
            tae = terrain_atlas[2][10];
            break;
        case LIME_WOOL:
            tae = terrain_atlas[2][9];
            break;
        case PINK_WOOL:
            tae = terrain_atlas[2][8];
            break;
        case GRAY_WOOL:
            tae = terrain_atlas[2][7];
            break;
        case LIGHT_GRAY_WOOL:
            tae = terrain_atlas[1][14];
            break;
        case CYAN_WOOL:
            tae = terrain_atlas[1][13];
            break;
        case PURPLE_WOOL:
            tae = terrain_atlas[1][12];
            break;
        case BLUE_WOOL:
            tae = terrain_atlas[1][11];
            break;
        case BROWN_WOOL:
            tae = terrain_atlas[1][10];
            break;
        case GREEN_WOOL:
            tae = terrain_atlas[1][9];
            break;
        case RED_WOOL:
            tae = terrain_atlas[1][8];
            break;
        case BLACK_WOOL:
            tae = terrain_atlas[1][7];
            break;
    }

    return tae;
}

void WoolRenderer::geometryNormalBlock(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    BlockRenderer::renderNormalBlockSide(local_x, local_y, local_z, side, getWoolTexture(block).current, c);
}

void WoolRenderer::drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y)
{
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, getWoolTexture(block).resized, dest, x, y);
}

const TerrainAtlasEntry &WoolRenderer::destructionTexture(const BLOCK_WDATA block) {
    switch (static_cast<COLOUR>(getBLOCKDATA(block))) {
        default:
            return terrain_atlas[0][4];
            break;
        case WHITE_WOOL:
            return terrain_atlas[0][4];
            break;
        case ORANGE_WOOL:
            return terrain_atlas[2][13];
            break;
        case MAGENTA_WOOL:
            return terrain_atlas[2][12];
            break;
        case LIGHT_BLUE_WOOL:
            return terrain_atlas[2][11];
            break;
        case YELLOW_WOOL:
            return terrain_atlas[2][10];
            break;
        case LIME_WOOL:
            return terrain_atlas[2][9];
            break;
        case PINK_WOOL:
            return terrain_atlas[2][8];
            break;
        case GRAY_WOOL:
            return terrain_atlas[2][7];
            break;
        case LIGHT_GRAY_WOOL:
            return terrain_atlas[1][14];
            break;
        case CYAN_WOOL:
            return terrain_atlas[1][13];
            break;
        case PURPLE_WOOL:
            return terrain_atlas[1][12];
            break;
        case BLUE_WOOL:
            return terrain_atlas[1][11];
            break;
        case BROWN_WOOL:
            return terrain_atlas[1][10];
            break;
        case GREEN_WOOL:
            return terrain_atlas[1][9];
            break;
        case RED_WOOL:
            return terrain_atlas[1][8];
            break;
        case BLACK_WOOL:
            return terrain_atlas[1][7];
            break;
    }
}

const char *WoolRenderer::getName(const BLOCK_WDATA block)
{
    switch (static_cast<COLOUR>(getBLOCKDATA(block))) {
        case WHITE_WOOL:
            return "White Wool";
        case ORANGE_WOOL:
            return "Orange Wool";
        case MAGENTA_WOOL:
            return "Magenta Wool";
        case LIGHT_BLUE_WOOL:
            return "Light Blue Wool";
        case YELLOW_WOOL:
            return "Yellow Wool";
        case LIME_WOOL:
            return "Lime Wool";
        case PINK_WOOL:
            return "Pink Wool";
        case GRAY_WOOL:
            return "Gray Wool";
        case LIGHT_GRAY_WOOL:
            return "Light Gray Wool";
        case CYAN_WOOL:
            return "Cyan Wool";
        case PURPLE_WOOL:
            return "Purple Wool";
        case BLUE_WOOL:
            return "Blue Wool";
        case BROWN_WOOL:
            return "Brown Wool";
        case GREEN_WOOL:
            return "Green Wool";
        case RED_WOOL:
            return "Red Wool";
        case BLACK_WOOL:
            return "Black Wool";
        default:
            return "Wool";
    }
}
