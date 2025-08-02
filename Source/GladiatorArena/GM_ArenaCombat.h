#pragma once

#if __has_include("CoreMinimal.h")
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#else
#include "UnrealStubs.h"
#endif

#if __has_include("GM_ArenaCombat.generated.h")
#include "GM_ArenaCombat.generated.h"
#endif

UCLASS()
class AGM_ArenaCombat : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGM_ArenaCombat();
};
