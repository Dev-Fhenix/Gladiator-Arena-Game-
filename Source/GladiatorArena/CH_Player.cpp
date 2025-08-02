#include "CH_Player.h"
#if __has_include("Camera/CameraComponent.h")
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"
#include "ConstructorHelpers.h"
#endif

ACH_Player::ACH_Player()
{
    PrimaryActorTick.bCanEverTick = false;

    bIsBlocking = false;
    bHasSword = false;
    bReplicates = true;

    // Create camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Create follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Set default mesh
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
    if (MeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);
        GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
        GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    }

    // Set default anim blueprint
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
    if (AnimBP.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(AnimBP.Class);
    }
}

void ACH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ACH_Player::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACH_Player::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ACH_Player::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ACH_Player::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACH_Player::LightAttack);
    PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &ACH_Player::Kick);
    PlayerInputComponent->BindAction("Block", IE_Pressed, this, &ACH_Player::StartBlock);
    PlayerInputComponent->BindAction("Block", IE_Released, this, &ACH_Player::StopBlock);
    PlayerInputComponent->BindAction("EquipSword", IE_Pressed, this, &ACH_Player::EquipSword);
}

void ACH_Player::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ACH_Player::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ACH_Player::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ACH_Player::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ACH_Player::LightAttack()
{
    // Placeholder for light attack logic
}

void ACH_Player::Kick()
{
    // Placeholder for kick logic
}

void ACH_Player::StartBlock()
{
    bIsBlocking = true;
}

void ACH_Player::StopBlock()
{
    bIsBlocking = false;
}

void ACH_Player::EquipSword()
{
    bHasSword = !bHasSword;
}

void ACH_Player::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    ACharacter::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACH_Player, bIsBlocking);
    DOREPLIFETIME(ACH_Player, bHasSword);
}

