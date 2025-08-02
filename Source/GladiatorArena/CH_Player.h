#pragma once

#if __has_include("CoreMinimal.h")
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#else
#include "UnrealStubs.h"
#endif

#if __has_include("CH_Player.generated.h")
#include "CH_Player.generated.h"
#endif

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACH_Player : public ACharacter
{
    GENERATED_BODY()

public:
    ACH_Player();

#if !__has_include("CoreMinimal.h")
    static UClass* StaticClass() { return nullptr; }
#endif

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    void LightAttack();
    void Kick();
    void StartBlock();
    void StopBlock();
    void EquipSword();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category="Combat")
    bool bIsBlocking;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category="Combat")
    bool bHasSword;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

