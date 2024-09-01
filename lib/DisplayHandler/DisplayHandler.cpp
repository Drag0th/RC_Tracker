#include <DisplayHandler.h>

void display_initialization(SSD1306AsciiWire &Display)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set2X();
    Display.println("  BOOTING ");
    Display.println("     UP    ");
}