#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_GladiatorCore.generated.h"

UCLASS()
class UGI_GladiatorCore : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
};
