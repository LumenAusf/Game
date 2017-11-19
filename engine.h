#ifndef ENGINE_H
#define ENGINE_H

namespace lumenausf {
    class Engine
    {
    public:
        Engine();
        static void Init(bool versionCritical = false);
    private:
        static bool CheckVersion();
    };
}
#endif // ENGINE_H
