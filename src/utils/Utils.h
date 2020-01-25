#pragma once

#include "Pokitto.h"
#include "Constants.h"
#include "Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


struct Rect {
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
};

namespace Utils {

    static inline bool sfxOver() {

        return ( PS::sfxDataPtr >= PS::sfxEndPtr );

    }
    
    static inline void printffloat(float d) {
        
        int a = static_cast<int>(d);
        int b = static_cast<int>((d * 1000)) % 1000;
        
        printf("%i.%i", a, b);
        
    }
        
    static inline bool collide(Rect rect1, Rect rect2) {
        return !(rect2.x                >= rect1.x + rect1.width  ||
                 rect2.x + rect2.width  <= rect1.x                ||
                 rect2.y                >= rect1.y + rect1.height ||
                 rect2.y + rect2.height <= rect1.y);
    }
    
    
    // This gets the length of an array at compile time
    template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {
    	return N;
    }
    
    static inline uint16_t getFrameCount() {
    
        return Pokitto::Core::frameCount;
    
    }
    
    static inline uint16_t getFrameCount(uint16_t mod) {
    
        return (Pokitto::Core::frameCount % mod);
    
    }
    
    static inline bool getFrameCountHalf(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) > (mod /2));
    
    }
    
    static inline bool isFrameCount(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) == 0);
    
    }
    
    static inline bool isFrameCount(uint16_t mod, uint16_t val) {
        
        return ((Pokitto::Core::frameCount % mod) == val);
    
    }
    
    
    static inline void drawDottedColumn(uint8_t x, uint8_t sy, uint8_t ey) {
        
        for (uint32_t y = sy; y <= ey; y = y + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
        
        for (uint32_t x = sx; x <= ex; x = x + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    
    // ----------------------------------------------------------------------------
    //  A better absolute as it uses less memory than the standard one .. 
    //
    template<typename T> T absT(const T & v) {
      
      return (v < 0) ? -v : v;
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint16_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint16_t value) {
    
      for (uint32_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint32_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint32_t value) {
    
      for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    

    // ----------------------------------------------------------------------------
    //  Start a stream from the SD card .. 
    //
    static void playMusicStream(SDStream stream) {

        #ifdef INCLUDE_SOUND_FROM_SD
        switch (stream) {

            case SDStream::StageIntro:
                PS::playMusicStream("music/galaxy1.raw", 0);
                break;

            case SDStream::ScoreTop:
                PS::playMusicStream("music/galaxy2.raw", 0);
                break;

            case SDStream::ScoreOther:
                PS::playMusicStream("music/galaxy3.raw", 0);
                break;

            case SDStream::ChallengeStart:
                PS::playMusicStream("music/galaxy4.raw", 0);
                break;

            case SDStream::ChallengeFinish:
                PS::playMusicStream("music/galaxy5.raw", 0);
                break;

            case SDStream::ChallengePerfect:
                PS::playMusicStream("music/galaxy6.raw", 0);
                break;

            case SDStream::FighterCaptured:
                PS::playMusicStream("music/galaxy7.raw", 0);
                break;

            case SDStream::FighterRescued:
                PS::playMusicStream("music/galaxy5.raw", 0);
                break;

            case SDStream::FighterDestroyed:
                PS::playMusicStream("music/galaxy6.raw", 0);
                break;

            case SDStream::Explosion:
                PS::playMusicStream("music/galaxyA.raw", 0);
                break;


        }
        #endif

    }

}
