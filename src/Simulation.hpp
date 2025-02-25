#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <QObject>
#include <string>
#include <vector>
#include "Point.hpp"
#undef main // This is added to undefine the main() from SDL

// Texture wrapper class
class LTexture
{
   public:
    LTexture();   // Initializes variables (constructor)
    ~LTexture();  // Deallocates memory (destructor)
    SDL_Texture* create_texture_from_surface(SDL_Renderer* sdlRenderer, SDL_Surface* surf,
                                             int format, SDL_Color* sdlColorKey,
                                             bool destroySurface);
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);  // Loads image at specified path
    // Gets image dimensions
    int getWidth();
    int getHeight();
    SDL_Texture* mTexture;  // The actual hardware texture

   private:
    // Image dimensions
    int mWidth;
    int mHeight;
};

class Simulation : public QObject
{
    Q_OBJECT
   public:
    Simulation(QObject* parent = 0) : QObject(parent)
    {
        // Initializes both objects as null, before each is assigned
        // an SDL object.
        gWindow   = NULL;
        gRenderer = NULL;
        Init();
        loadTextures();
        clearScreen();
    }
    ~Simulation();
    void renderAgent(std::vector<Point<int>>, std::vector<int>);   // update/render agent
    void renderTarget(std::vector<Point<int>>, std::vector<int>);  // update/render target
    void clearScreen();

   private:
    // Screen dimension constants
    const int kScreenWidth  = 1000;  // 640
    const int kScreenHeight = 1000;  // 480
    // SDL objects
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool Init();
    bool loadTextures();
    LTexture AgentTexture[5];   // Array containing 5 images for 5 Agents
    LTexture TargetTexture[5];  // Array containing 5 images for 5 Targets
};

#endif
