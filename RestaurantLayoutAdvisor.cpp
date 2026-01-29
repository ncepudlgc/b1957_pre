// RestaurantLayoutAdvisor.cpp
#include <iostream>
#include <vector>
#include <iomanip>

struct Table {
    int x, y;  // Position of table (top-left corner)
    Table(int x, int y) : x(x), y(y) {}
};

struct Pillar {
    int x, y;  // Position of pillar (top-left corner)
    int width, height;
    Pillar(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
};

// Check if a position overlaps with the pillar
bool overlapsWithPillar(int x, int y, int width, int depth, const Pillar& pillar) {
    int tableRight = x + width;
    int tableBottom = y + depth;
    int pillarRight = pillar.x + pillar.width;
    int pillarBottom = pillar.y + pillar.height;
    
    return !(tableRight <= pillar.x || x >= pillarRight || tableBottom <= pillar.y || y >= pillarBottom);
}

// Calculate optimal table layout for given room dimensions
std::vector<Table> calculateTableLayout(int roomWidth, int roomHeight, int tableWidth, int tableDepth, int chairDepth, int spacing, const Pillar& pillar) {
    std::vector<Table> tables;

    // Calculate table units and spacing between them to determine the size of blocks to place
    // Chairs are placed on all 4 sides, so we need space for chairs on both width and depth sides
    int tableUnitWidth = tableWidth + 2 * chairDepth; // Chairs on left and right
    int tableUnitDepth = tableDepth + 2 * chairDepth; // Chairs on top and bottom
    int blockWidth = tableUnitWidth + spacing;
    int blockDepth = tableUnitDepth + spacing;

    // Calculate how many blocks fit (taking into account that spacing is not needed after the final block)
    int tablesPerRow = (roomWidth + spacing) / blockWidth;
    int tablesPerCol = (roomHeight + spacing) / blockDepth;

    // Place tables with proper spacing, avoiding the pillar
    for (int row = 0; row < tablesPerCol; row++) {
        for (int col = 0; col < tablesPerRow; col++) {
            int x = col * blockWidth + chairDepth; // Offset by chair depth for left chair
            int y = row * blockDepth + chairDepth; // Offset by chair depth for top chair
            
            // Check if this table position overlaps with the pillar
            if (!overlapsWithPillar(x, y, tableWidth, tableDepth, pillar)) {
                tables.push_back(Table(x, y));
            }
        }
    }

    return tables;
}

// Print layout using text graphics
void printLayout(const std::vector<Table>& tables, int roomWidth, int roomHeight, const Pillar& pillar) {
    // Create grid (1 char = 1 foot)
    std::vector<std::vector<char>> grid(roomHeight, std::vector<char>(roomWidth, '.'));

    // Mark pillar first (8x8 in center)
    for (int y = pillar.y; y < pillar.y + pillar.height; y++) {
        for (int x = pillar.x; x < pillar.x + pillar.width; x++) {
            if (x < roomWidth && y < roomHeight) {
                grid[y][x] = 'P';
            }
        }
    }

    // Mark tables and chairs
    for (const auto& table : tables) {
        // Mark table (4x4)
        for (int y = table.y; y < table.y + 4; y++) {
            for (int x = table.x; x < table.x + 4; x++) {
                if (x < roomWidth && y < roomHeight && grid[y][x] != 'P') {
                    grid[y][x] = 'T';
                }
            }
        }

        // Mark chairs (2x2 on all 4 sides of table) - 4 chairs total
        // Top chair
        for (int y = table.y - 2; y < table.y; y++) {
            for (int x = table.x + 1; x < table.x + 3; x++) {
                if (x >= 0 && x < roomWidth && y >= 0 && y < roomHeight && grid[y][x] != 'P') {
                    grid[y][x] = 'C';
                }
            }
        }
        // Bottom chair
        for (int y = table.y + 4; y < table.y + 6; y++) {
            for (int x = table.x + 1; x < table.x + 3; x++) {
                if (x >= 0 && x < roomWidth && y >= 0 && y < roomHeight && grid[y][x] != 'P') {
                    grid[y][x] = 'C';
                }
            }
        }
        // Left chair
        for (int y = table.y + 1; y < table.y + 3; y++) {
            for (int x = table.x - 2; x < table.x; x++) {
                if (x >= 0 && x < roomWidth && y >= 0 && y < roomHeight && grid[y][x] != 'P') {
                    grid[y][x] = 'C';
                }
            }
        }
        // Right chair
        for (int y = table.y + 1; y < table.y + 3; y++) {
            for (int x = table.x + 4; x < table.x + 6; x++) {
                if (x >= 0 && x < roomWidth && y >= 0 && y < roomHeight && grid[y][x] != 'P') {
                    grid[y][x] = 'C';
                }
            }
        }
    }

    // Print grid
    std::cout << "\nRestaurant Layout (" << roomWidth << "' x " << roomHeight << "'):\n";
    std::cout << "T = Table, C = Chair, P = Pillar, . = Empty space\n\n";

    for (int y = 0; y < roomHeight; y++) {
        for (int x = 0; x < roomWidth; x++) {
            std::cout << grid[y][x];
        }
        std::cout << "\n";
    }

    std::cout << "\nTotal tables: " << tables.size() << "\n";
    std::cout << "Total seating capacity: " << tables.size() * 4 << " people\n";
}

int main() {
    // Define variable room size (feet)
    int roomWidth = 50;
    int roomHeight = 35;

    // Define fixed parameters (feet)
    const int tableWidth = 4;
    const int tableDepth = 4; // Changed to 4x4 tables
    const int chairDepth = 2;
    const int spacing = 1;
    const int pillarSize = 8; // 8x8 pillar

    // Calculate pillar position (center of room)
    int pillarX = (roomWidth - pillarSize) / 2;
    int pillarY = (roomHeight - pillarSize) / 2;
    Pillar pillar(pillarX, pillarY, pillarSize, pillarSize);

    std::cout << "Restaurant Layout Advisor\n";
    std::cout << "=========================\n";
    std::cout << "Table size: 4' x 4' with four 2' x 2' chairs (one on each side)\n";
    std::cout << "8' x 8' pillar in center of room\n";
    std::cout << "Minimum 1' spacing between all furniture\n";

    // Calculate optimal layout
    std::vector<Table> tables = calculateTableLayout(roomWidth, roomHeight, tableWidth, tableDepth, chairDepth, spacing, pillar);

    // Display results
    printLayout(tables, roomWidth, roomHeight, pillar);

    return 0;
}