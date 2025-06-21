#include "common/main.h"
#include "components.h"
#include "screenImports.h"

void setupRenderingScreens(std::vector<std::unique_ptr<defaultScreenTYPE__sys>> &renderingScreens)
{
    renderingScreens.reserve(10);
    renderingScreens.push_back(std::make_unique<RedScreen>());
}
