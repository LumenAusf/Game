#include "enginecore.h"

namespace LumenAusf
{
    EngineCore* EngineCore::EnCore = nullptr;

    Engine::Engine ()
    {
        if (EngineCore::EnCore == nullptr)
            EngineCore::EnCore = new EngineCore ();
        else
        {
            EngineCore::EnCore->Finish ();
            EngineCore::EnCore = new EngineCore ();
        }
    }

    void Engine::Init (bool versionCritical, int width, int height, std::string windowName)
    {
        EngineCore::EnCore->Init (versionCritical, width, height, windowName);
    }

    void Engine::ReadEvent () { EngineCore::EnCore->ReadEvent (this); }

    void Engine::Finish () { EngineCore::EnCore->Finish (); }

    Texture* Engine::CreateTexture (std::string_view path, int hCount, int wCount)
    {
        return EngineCore::EnCore->CreateTexture (path, hCount, wCount);
    }

    void Engine::DestroyTexture (Texture* t) { EngineCore::EnCore->DestroyTexture (t); }

    void Engine::DrawTriangle (const tri0& t, const Color& c) { EngineCore::EnCore->DrawTriangle (t, c); }

    void Engine::DrawTriangle (const tri1& t) { EngineCore::EnCore->DrawTriangle (t); }

    void Engine::DrawTriangle (const tri2& t, Texture* tex) { EngineCore::EnCore->DrawTriangle (t, tex); }

    void Engine::DrawTriangle (const tri2& t, Texture* tex, const mat2x3& m) { EngineCore::EnCore->DrawTriangle (t, tex, m); }

    float Engine::getTimeFromInit (bool isSec) { return EngineCore::EnCore->getTimeFromInit (isSec); }

    void Engine::setTimePrevious (float sec) { EngineCore::setTimePrevious (sec); }

    float Engine::getTimePrevious () { return EngineCore::getTimePrevious (); }

    float Engine::getDeltaTime () { return EngineCore::getDeltaTime (); }

    void Engine::SwapBuffers () { EngineCore::EnCore->SwapBuffers (); }

    void Engine::Clear () { EngineCore::EnCore->Clear (); }
}
