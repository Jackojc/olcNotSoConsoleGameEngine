#pragma once


#include <atomic>
#include <condition_variable>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <chrono>
#include <iostream>
#include <utility>
#include <cmath>
#include <deque>
#include <cstddef>
#include <list>
#include <locale>
#include <codecvt>
#include <cstdint>
#include <cstring>



#include <SDL2/SDL.h>


constexpr int FONT_SIZE_W = 8;
constexpr int FONT_SIZE_H = 8;
constexpr int FONT_SIZE_BORDER = 1;





#define VK_SPACE SDL_SCANCODE_SPACE
#define VK_UP SDL_SCANCODE_UP
#define VK_DOWN SDL_SCANCODE_DOWN
#define VK_LEFT SDL_SCANCODE_LEFT
#define VK_RIGHT SDL_SCANCODE_RIGHT

#define VK_MOUSE_LEFT 0
#define VK_MOUSE_RIGHT 1
#define VK_MOUSE_MIDDLE 2







struct two_colour {
    SDL_Color fg;
    SDL_Color bg;
};


struct colours {
    uint8_t code;
    SDL_Color colour;
};












enum COLOUR: uint8_t {
    FG_BLACK        = 0x0000,
    FG_DARK_BLUE    = 0x0001,
    FG_DARK_GREEN   = 0x0002,
    FG_DARK_CYAN    = 0x0003,
    FG_DARK_RED     = 0x0004,
    FG_DARK_MAGENTA = 0x0005,
    FG_DARK_YELLOW  = 0x0006,
    FG_GREY         = 0x0007,
    FG_DARK_GREY    = 0x0008,
    FG_BLUE         = 0x0009,
    FG_GREEN        = 0x000A,
    FG_CYAN         = 0x000B,
    FG_RED          = 0x000C,
    FG_MAGENTA      = 0x000D,
    FG_YELLOW       = 0x000E,
    FG_WHITE        = 0x000F,

    BG_BLACK        = 0x0000,
    BG_DARK_BLUE    = 0x0010,
    BG_DARK_GREEN   = 0x0020,
    BG_DARK_CYAN    = 0x0030,
    BG_DARK_RED     = 0x0040,
    BG_DARK_MAGENTA = 0x0050,
    BG_DARK_YELLOW  = 0x0060,
    BG_GREY         = 0x0070,
    BG_DARK_GREY    = 0x0080,
    BG_BLUE         = 0x0090,
    BG_GREEN        = 0x00A0,
    BG_CYAN         = 0x00B0,
    BG_RED          = 0x00C0,
    BG_MAGENTA      = 0x00D0,
    BG_YELLOW       = 0x00E0,
    BG_WHITE        = 0x00F0
};


constexpr SDL_Color colour_lookup[] = {
    SDL_Color{0,0,0,255},      // 0
    SDL_Color{0,0,127,255},    // 1
    SDL_Color{0,127,0,255},    // 2
    SDL_Color{0,127,127,255},  // 3
    SDL_Color{127,0,0,255},    // 4
    SDL_Color{127,0,127,255},  // 5
    SDL_Color{127,127,0,255},  // 6
    SDL_Color{127,127,127,255},// 7
    SDL_Color{0,0,0,255},      // 8
    SDL_Color{0,0,255,255},    // 9
    SDL_Color{0,255,0,255},    // A
    SDL_Color{0,255,255,255},  // B
    SDL_Color{255,0,0,255},    // C
    SDL_Color{255,0,255,255},  // D
    SDL_Color{255,255,0,255},  // E
    SDL_Color{255,255,255,255},// F
};


constexpr std::array<colours, 16> FG = {
    colours{FG_BLACK,        colour_lookup[0]},
    colours{FG_DARK_BLUE,    colour_lookup[1]},
    colours{FG_DARK_GREEN,   colour_lookup[2]},
    colours{FG_DARK_CYAN,    colour_lookup[3]},
    colours{FG_DARK_RED,     colour_lookup[4]},
    colours{FG_DARK_MAGENTA, colour_lookup[5]},
    colours{FG_DARK_YELLOW,  colour_lookup[6]},
    colours{FG_GREY,         colour_lookup[7]},
    colours{FG_DARK_GREY,    colour_lookup[8]},
    colours{FG_BLUE,         colour_lookup[9]},
    colours{FG_GREEN,        colour_lookup[10]},
    colours{FG_CYAN,         colour_lookup[11]},
    colours{FG_RED,          colour_lookup[12]},
    colours{FG_MAGENTA,      colour_lookup[13]},
    colours{FG_YELLOW,       colour_lookup[14]},
    colours{FG_WHITE,        colour_lookup[15]}
};


constexpr std::array<colours, 16> BG = {
    colours{BG_BLACK,        colour_lookup[0]},
    colours{BG_DARK_BLUE,    colour_lookup[1]},
    colours{BG_DARK_GREEN,   colour_lookup[2]},
    colours{BG_DARK_CYAN,    colour_lookup[3]},
    colours{BG_DARK_RED,     colour_lookup[4]},
    colours{BG_DARK_MAGENTA, colour_lookup[5]},
    colours{BG_DARK_YELLOW,  colour_lookup[6]},
    colours{BG_GREY,         colour_lookup[7]},
    colours{BG_DARK_GREY,    colour_lookup[8]},
    colours{BG_BLUE,         colour_lookup[9]},
    colours{BG_GREEN,        colour_lookup[10]},
    colours{BG_CYAN,         colour_lookup[11]},
    colours{BG_RED,          colour_lookup[12]},
    colours{BG_MAGENTA,      colour_lookup[13]},
    colours{BG_YELLOW,       colour_lookup[14]},
    colours{BG_WHITE,        colour_lookup[15]}
};

std::array<two_colour, 256> generate_lookup_table() {
    std::array<two_colour, 256> table;

    for (int a = 0; a < 16; ++a) {
        for (int b = 0; b < 16; ++b) {
            table[FG[a].code | BG[b].code] = {FG[a].colour, BG[b].colour};
        }
    }

    return table;
}

std::array<two_colour, 256> COLOUR_LOOKUP;








enum PIXEL_TYPE
{
    PIXEL_SOLID = 254,
    PIXEL_THREEQUARTERS = 219,
    PIXEL_HALF = 220,
    PIXEL_QUARTER = 223,
    PIXEL_BORDER = 255,
    PIXEL_LEFT = 221,
    PIXEL_RIGHT = 222
};


struct sKeyState {
    bool bPressed;
    bool bReleased;
    bool bHeld;
};




struct Point {
    int x, y;
};






class olcConsoleGameEngine {
    public:
        sKeyState m_mouse[5];
        sKeyState* m_keys;

        int m_mousePosX;
        int m_mousePosY;

    private:
        SDL_Window* m_window;
        SDL_Renderer* m_render;

        int m_numKeys;
        Uint8* m_keyOldState;
        const Uint8* m_keyNewState;

        bool m_mouseOldState[5];
        bool m_mouseNewState[5];

        int m_nScreenWidth;
        int m_nScreenHeight;

        int m_nFontWidth;
        int m_nFontHeight;

        int m_nScreenWidthPixels;
        int m_nScreenHeightPixels;

        SDL_Texture* m_fontFile;
        SDL_Texture* m_shapeBuffer;
        SDL_Texture* m_shapeBuffer2;
        SDL_Texture* m_fontBuffer;
        Uint32* m_windowPixels;

        std::atomic<bool> m_bAtomActive;
        std::condition_variable m_cvGameFinished;
        std::mutex m_muxGame;

        std::string m_sTitle;

    public:
        std::wstring m_sAppName;


    public:
        olcConsoleGameEngine() {
            COLOUR_LOOKUP = generate_lookup_table();
            m_sTitle.reserve(256);
        }


        ~olcConsoleGameEngine() {

        }





    public:
        void Error(const std::string& msg) {
            std::cerr << "ERROR: " << msg << '\n';
        }


        void ErrorSDL(const std::string& msg) {
            std::cerr << "ERROR: " << msg << "\n\t" << SDL_GetError() << "!\n";
        }






    private:
        template <typename T>
        void CheckFailure(T* ptr, const std::string& msg) {
            if (ptr == nullptr)
                ErrorSDL(msg);
        }




        Point TranslateCoordsToPixels(int x, int y) {
            return {
                x * m_nFontWidth,
                y * m_nFontHeight
            };
        }




        void LoadFontFile(const std::string& fname) {
            // Load image.
            SDL_Surface* temp = SDL_LoadBMP(fname.c_str());
            CheckFailure(temp, "SDL_LoadBMP returned an error!");


            // set color key to 255,0,255; this basically makes
            // it transparent.
            if (SDL_SetColorKey(
                temp,
                SDL_TRUE,
                SDL_MapRGB(temp->format, 255, 0, 255)
            ) < 0)
                ErrorSDL("SDL_SetColorKey returned an error!");


            // Convert to texture.
            m_fontFile = SDL_CreateTextureFromSurface(
                m_render,
                temp
            );
            CheckFailure(
                m_fontFile,
                "SDL_CreateTextureFromSurface returned an error!"
            );


            // Cleanup and return.
            SDL_FreeSurface(temp);
        }



        Point CharIndexFontFile(uint8_t c) {
            // font file is 16x16 tiles.
            return {
                c % 16,  // x
                c / 16   // y
            };
        }




        void SetWindowTitle(float fps) {
            SDL_SetWindowTitle(
                m_window,
                (m_sTitle + std::to_string(fps)).c_str()
            );
        }







        void SetupKeyboard() {
            m_keyNewState = SDL_GetKeyboardState(&m_numKeys);
            m_keyOldState = new Uint8[m_numKeys];
            m_keys = new sKeyState[m_numKeys];
        }


        void SetupWindow() {
            m_window = SDL_CreateWindow(
                m_sTitle.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_nScreenWidthPixels,
                m_nScreenHeightPixels,
                SDL_WINDOW_SHOWN
            );
            CheckFailure(m_window, "SDL_CreateWindow returned an error!");
        }


        void SetupRenderer() {
            m_render = SDL_CreateRenderer(
                m_window,
                -1,
                SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC |
                SDL_RENDERER_TARGETTEXTURE
            );
            CheckFailure(
                m_render,
                "SDL_CreateRenderer returned an error!"
            );
        }


        void SetupInitModules() {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
                ErrorSDL("SDL_Init returned an error!");
        }


        void SetupSDL() {
            SetupInitModules();
            SetupWindow();
            SetupRenderer();
            SetupKeyboard();

            LoadFontFile("./font.bmp");

            m_windowPixels = new Uint32[(m_nScreenWidth + 1) * (m_nScreenHeight + 1)];

            m_shapeBuffer = SDL_CreateTexture(
                m_render,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                m_nScreenWidth,
                m_nScreenHeight
            );

            m_shapeBuffer2 = SDL_CreateTexture(
                m_render,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_TARGET,
                m_nScreenWidth,
                m_nScreenHeight
            );

            m_fontBuffer = SDL_CreateTexture(
                m_render,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_TARGET,
                m_nScreenWidthPixels,
                m_nScreenHeightPixels
            );

            SDL_SetRenderTarget(m_render, m_fontBuffer);


            SetWindowTitle(0.0f);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
        }




        void QuitSDL() {
            SDL_DestroyTexture(m_fontBuffer);
            SDL_DestroyTexture(m_shapeBuffer2);
            SDL_DestroyTexture(m_shapeBuffer);

            delete[] m_windowPixels;

            SDL_DestroyTexture(m_fontFile);

            delete[] m_keys;
            delete[] m_keyOldState;

            SDL_DestroyRenderer(m_render);
            SDL_DestroyWindow(m_window);

            SDL_Quit();
        }










    private:
        void UpdateMouseState() {
            Uint32 state = SDL_GetMouseState(&m_mousePosX, &m_mousePosY);

            m_mousePosX /= m_nFontWidth;
            m_mousePosY /= m_nFontHeight;

            m_mouseNewState[0] = state & SDL_BUTTON_LMASK;  // left
            m_mouseNewState[1] = state & SDL_BUTTON_RMASK;  // right
            m_mouseNewState[2] = state & SDL_BUTTON_MMASK;  // middle


            for (int m = 0; m < 5; ++m) {
                m_mouse[m].bPressed = false;
                m_mouse[m].bReleased = false;

                if (m_mouseNewState[m] != m_mouseOldState[m]) {
                    if (m_mouseNewState[m]) {
                        m_mouse[m].bPressed = true;
                        m_mouse[m].bHeld = true;
                    } else {
                        m_mouse[m].bReleased = true;
                        m_mouse[m].bHeld = false;
                    }
                }

                m_mouseOldState[m] = m_mouseNewState[m];
            }


            std::copy(
                m_mouseNewState,
                m_mouseNewState + 5,
                m_mouseOldState
            );
        }


        void UpdateKeyboardState() {
            for (int i = 0; i < m_numKeys; ++i) {
                m_keys[i].bPressed = false;
                m_keys[i].bReleased = false;

                if (m_keyNewState[i] != m_keyOldState[i]) {
                    if (m_keyNewState[i] == true) {
                        m_keys[i].bPressed = !m_keys[i].bHeld;
                        m_keys[i].bHeld = true;
                    } else {
                        m_keys[i].bReleased = true;
                        m_keys[i].bHeld = false;
                    }
                }

                m_keyOldState[i] = m_keyNewState[i];
            }

            std::copy(
                m_keyNewState,
                m_keyNewState + m_numKeys,
                m_keyOldState
            );
        }





        void UpdatePreFrame() {
            SDL_Event e;

            while (SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        m_bAtomActive = false;
                        goto breakOut;
                        break;
                }
            }
            breakOut:

            UpdateKeyboardState();
            UpdateMouseState();
        }










        void DrawBG(
            int x,
            int y,
            SDL_Color& col
        ) {
            int r = col.r;
            int g = col.g;
            int b = col.b;
            int a = col.a;

            m_windowPixels[(y * m_nScreenWidth) + x] =
                (a << 24) + (r << 16) + (g << 8) + b;
        }


        void DrawFG(
            int x,
            int y,
            uint8_t c,
            SDL_Color& col
        ) {
            SDL_SetRenderTarget(m_render, m_fontBuffer);

            Point pt = CharIndexFontFile(c);
            SDL_Rect src = {
                pt.x * (FONT_SIZE_W + FONT_SIZE_BORDER),
                pt.y * (FONT_SIZE_H + FONT_SIZE_BORDER),
                FONT_SIZE_W,
                FONT_SIZE_H
            };
            SDL_Rect dst = {
                x * m_nFontWidth,
                y * m_nFontHeight,
                m_nFontWidth,
                m_nFontHeight
            };

            // set colour of font
            SDL_SetTextureColorMod(m_fontFile, col.r, col.g, col.b);
            SDL_SetTextureAlphaMod(m_fontFile, col.a);

            SDL_RenderCopy(
                m_render,
                m_fontFile,
                &src,
                &dst
            );
        }











        void UpdatePostFrame() {
            SDL_SetRenderTarget(m_render, nullptr);

            SDL_UpdateTexture(
                m_shapeBuffer,
                nullptr,
                m_windowPixels,
                (m_nScreenWidth) * sizeof(Uint32)
            );

            std::memset(
                m_windowPixels,
                (255 << 24) + (0 << 16) + (0 << 8) + 0,
                (m_nScreenWidth * m_nScreenHeight) * sizeof(Uint32)
            );

            SDL_RenderCopy(m_render, m_shapeBuffer, nullptr, nullptr);
            SDL_RenderCopy(m_render, m_fontBuffer, nullptr, nullptr);

            SDL_RenderPresent(m_render);

            SDL_SetRenderTarget(m_render, m_fontBuffer);
            SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
            SDL_RenderClear(m_render);
        }

















    public:
        int ConstructConsole(int width, int height, int fontw, int fonth) {
            m_nScreenWidth = width;
            m_nScreenHeight = height;

            m_nFontWidth = fontw;
            m_nFontHeight = fonth;

            m_nScreenWidthPixels = width * fontw;
            m_nScreenHeightPixels = height * fonth;

            m_sTitle.append("OneLoneCoder.com - Console Game Engine - ")
            .append(std::string(m_sAppName.begin(), m_sAppName.end()))
            .append(" - FPS: ");

            return 1;
        }


        int ScreenWidth() {
            return m_nScreenWidth;
        }


        int ScreenHeight() {
            return m_nScreenHeight;
        }








    public:
        sKeyState GetKey(int i) {
            return m_keys[i];
        }


        sKeyState GetMouse(int i) {
            return m_mouse[i];
        }





    public:

        void Clip(int& x, int& y) {
            if (x < 0) x = 0;
            if (x >= m_nScreenWidth) x = m_nScreenWidth;
            if (y < 0) y = 0;
            if (y >= m_nScreenHeight) y = m_nScreenHeight;
        }

        virtual void Draw(
            int x,
            int y,
            uint8_t c = PIXEL_SOLID,
            uint16_t col = FG_WHITE | BG_BLACK
        ) {
            two_colour& cols = COLOUR_LOOKUP[col];

            Clip(x, y);

            DrawFG(x, y, c, cols.fg);
            DrawBG(x, y, cols.bg);
        }

        void Fill(int x1, int y1, int x2, int y2, uint8_t c = PIXEL_SOLID, uint16_t col = FG_WHITE | BG_BLACK)
        {
            SDL_Color& cols = COLOUR_LOOKUP[col].bg;

            const SDL_Rect r = {x1, y1, x2, y2};

            SDL_SetRenderTarget(m_render, m_shapeBuffer2);
            SDL_SetRenderDrawColor(m_render, cols.r, cols.g, cols.b, cols.a);
            SDL_RenderFillRect(m_render, &r);
        }

        void DrawString(int x, int y, const std::string& c, uint16_t col = FG_WHITE | BG_BLACK)
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                Draw(x + i, y, c[i], col);
            }
        }


        void DrawStringAlpha(int x, int y, const std::string& c, uint16_t col = FG_WHITE | BG_BLACK)
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                if (c[i] != ' ')
                    Draw(x + i, y, c[i], col);
            }
        }


        void DrawString(int x, int y, const std::wstring& c, uint16_t col = FG_WHITE | BG_BLACK)
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                Draw(x + i, y, c[i], col);
            }
        }


        void DrawStringAlpha(int x, int y, const std::wstring& c, uint16_t col = FG_WHITE | BG_BLACK)
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                if (c[i] != L' ')
                    Draw(x + i, y, c[i], col);
            }
        }


        void DrawLine(int x1, int y1, int x2, int y2, uint8_t c = PIXEL_SOLID, uint16_t col = FG_WHITE | BG_BLACK)
        {
            SDL_Color& cols = COLOUR_LOOKUP[col].bg;

            SDL_SetRenderTarget(m_render, m_shapeBuffer2);
            SDL_SetRenderDrawColor(m_render, cols.r, cols.g, cols.b, cols.a);
            SDL_RenderDrawLine(m_render, x1, y1, x2, y2);
        }

        void DrawCircle(int xc, int yc, int r, uint8_t c = PIXEL_SOLID, uint16_t col = FG_WHITE | BG_BLACK)
        {

            int x = 0;
            int y = r;
            int p = 3 - 2 * r;
            if (!r) return;

            while (y >= x) // only formulate 1/8 of circle
            {
                Draw(xc - x, yc - y, c, col);//upper left left
                Draw(xc - y, yc - x, c, col);//upper upper left
                Draw(xc + y, yc - x, c, col);//upper upper right
                Draw(xc + x, yc - y, c, col);//upper right right
                Draw(xc - x, yc + y, c, col);//lower left left
                Draw(xc - y, yc + x, c, col);//lower lower left
                Draw(xc + y, yc + x, c, col);//lower lower right
                Draw(xc + x, yc + y, c, col);//lower right right
                if (p < 0) p += 4 * x++ + 6;
                else p += 4 * (x++ - y--) + 10;
            }
        }

        /*void DrawSprite(int x, int y, olcSprite *sprite)
        {
            if (sprite == nullptr)
                return;

            for (int i = 0; i < sprite->nWidth; i++)
            {
                for (int j = 0; j < sprite->nHeight; j++)
                {
                    if (sprite->GetGlyph(i, j) != L' ')
                        Draw(x + i, y + j, sprite->GetGlyph(i, j), sprite->GetColour(i, j));
                }
            }
        }

        void DrawPartialSprite(int x, int y, olcSprite *sprite, int ox, int oy, int w, int h)
        {
            if (sprite == nullptr)
                return;

            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    if (sprite->GetGlyph(i+ox, j+oy) != L' ')
                        Draw(x + i, y + j, sprite->GetGlyph(i+ox, j+oy), sprite->GetColour(i+ox, j+oy));
                }
            }
        }*/

        void DrawWireFrameModel(const std::vector<std::pair<float, float>> &vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, uint16_t col = FG_WHITE | BG_BLACK)
        {
            // pair.first = x coordinate
            // pair.second = y coordinate

            // Create translated model vector of coordinate pairs
            std::vector<std::pair<float, float>> vecTransformedCoordinates;
            int verts = vecModelCoordinates.size();
            vecTransformedCoordinates.resize(verts);

            // Rotate
            for (int i = 0; i < verts; i++)
            {
                vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
                vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
            }

            // Scale
            for (int i = 0; i < verts; i++)
            {
                vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
                vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
            }

            // Translate
            for (int i = 0; i < verts; i++)
            {
                vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
                vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
            }

            // Draw Closed Polygon
            for (int i = 0; i < verts + 1; i++)
            {
                int j = (i + 1);
                DrawLine((int)vecTransformedCoordinates[i % verts].first, (int)vecTransformedCoordinates[i % verts].second,
                    (int)vecTransformedCoordinates[j % verts].first, (int)vecTransformedCoordinates[j % verts].second, PIXEL_SOLID, col);
            }
        }









    public:
        virtual bool OnUserCreate() = 0;
        virtual bool OnUserUpdate(float fElapsedTime) = 0;







    private:
        void Frame(float fElapsedTime) {
            UpdatePreFrame();

            if (!OnUserUpdate(fElapsedTime))
                m_bAtomActive = false;

            unsigned fps = std::floor(1.0f / fElapsedTime);
            SetWindowTitle(fps);

            UpdatePostFrame();
        }


        void GameThread() {
            SetupSDL();


            if (!OnUserCreate())
                m_bAtomActive = false;


            auto tp1 = std::chrono::system_clock::now();
            auto tp2 = std::chrono::system_clock::now();


            // Run as fast as possible
            while (m_bAtomActive) {
                tp2 = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsedTime = tp2 - tp1;
                tp1 = tp2;

                Frame(elapsedTime.count());
            }


            QuitSDL();
            m_cvGameFinished.notify_one();
        }


    public:
        void Start() {
            m_bAtomActive = true;

            // Star the thread
            std::thread t(&olcConsoleGameEngine::GameThread, this);

            // Wait for thread to be exited
            std::unique_lock<std::mutex> ul(m_muxGame);
            m_cvGameFinished.wait(ul);

            // Tidy up
            t.join();
        }
};
